#include <Rcpp.h>
using namespace Rcpp;

#include "Iconv.h"

Iconv::Iconv(const std::string& from, const std::string& to) {
  if (from == "UTF-8") {
    cd_ = NULL;
  } else {
    cd_ = Riconv_open(to.c_str(), from.c_str());
    if (cd_ == (void*)-1) {
      if (errno == EINVAL) {
        stop("Can't convert from %s to %s", from, to);
      } else {
        stop("Iconv initialisation failed");
      }
    }

    // Allocate space in buffer
    buffer_.resize(1024);
  }
}

Iconv::~Iconv() {
  if (cd_ != NULL) {
    Riconv_close(cd_);
    cd_ = NULL;
  }
}

size_t Iconv::convert(const char* start, const char* end) {
  size_t n = end - start;

  // Ensure buffer is big enough: one input byte can never generate
  // more than 4 output bytes
  size_t max_size = n * 4;
  if (buffer_.size() < max_size)
    buffer_.resize(max_size);

  char* outbuf = &buffer_[0];
  size_t inbytesleft = n, outbytesleft = max_size;
  size_t res = Riconv(cd_, &start, &inbytesleft, &outbuf, &outbytesleft);

  if (res == (size_t)-1) {
    switch (errno) {
    case EILSEQ:
      stop("Invalid multibyte sequence");
    case EINVAL:
      stop("Incomplete multibyte sequence");
    case E2BIG:
      stop("Iconv buffer too small");
    default:
      stop("Iconv failed to convert for unknown reason");
    }
  }

  return max_size - outbytesleft;
}

int my_strnlen(const char* s, int maxlen) {
  for (int n = 0; n < maxlen; ++n) {
    if (s[n] == '\0')
      return n;
  }
  return maxlen;
}

#if defined(__sun)
#define readr_strnlen my_strnlen
#else
#define readr_strnlen strnlen
#endif

// To be safe, we need to check for nulls - this also needs to emit
// a warning, but this behaviour is better than crashing
SEXP safeMakeChar(const char* start, size_t n, bool hasNull) {
  size_t m = hasNull ? readr_strnlen(start, n) : n;
  if (m > INT_MAX) {
    Rf_error("R character strings are limited to 2^31-1 bytes");
  }
  return Rf_mkCharLenCE(start, m, CE_UTF8);
}

SEXP Iconv::makeSEXP(const char* start, const char* end, bool hasNull) {
  if (cd_ == NULL)
    return safeMakeChar(start, end - start, hasNull);

  int n = convert(start, end);
  return safeMakeChar(&buffer_[0], n, hasNull);
}

std::string Iconv::makeString(const char* start, const char* end) {
  if (cd_ == NULL)
    return std::string(start, end);

  int n = convert(start, end);
  return std::string(&buffer_[0], n);
}
