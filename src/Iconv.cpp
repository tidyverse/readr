#include <Rcpp.h>
using namespace Rcpp;

#include "Iconv.h"

Iconv::Iconv(const std::string& from, const std::string& to) {
  if (from == "UTF-8") {
    cd_ = NULL;
  } else {
    cd_ = Riconv_open(to.c_str(), from.c_str());
    if (cd_ == (void*) -1) {
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

SEXP Iconv::makeSEXP(const char* start, const char* end) {
  size_t n = end - start;
  if (cd_ == NULL)
    return Rf_mkCharLenCE(start, n, CE_UTF8);

  // Ensure buffer is big enough: one input byte can never generate
  // more than 4 output bytes
  size_t max_size = n * 4;
  if (buffer_.size() < max_size)
    buffer_.resize(max_size);

  char* outbuf = &buffer_[0];
  size_t inbytesleft = n, outbytesleft = max_size;
  size_t res = Riconv(cd_, &start, &inbytesleft, &outbuf, &outbytesleft);

  if (res == (size_t) -1) {
    switch(errno) {
    case EILSEQ: stop("Invalid multibyte sequence");
    case EINVAL: stop("Incomplete multibyte sequence");
    case E2BIG:  stop("Iconv buffer too small");
    default:     stop("Iconv failed to convert for unknown reason");
    }
  }

  return Rf_mkCharLenCE(&buffer_[0], max_size - outbytesleft, CE_UTF8);
}
