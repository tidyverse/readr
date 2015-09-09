#include <Rcpp.h>
using namespace Rcpp;

#include "Iconv.h"

SEXP Iconv::makeSEXP(const char* start, const char* end) {
  size_t n = end - start;
  if (cd_ == NULL)
    return Rf_mkCharLenCE(start, n, CE_UTF8);

  // Ensure buffer is big enough: one input byte can never generate
  // more than 4 output bytes
  size_t max_size = n * 4;
  if (buffer_.size() < max_size)
    buffer_.resize(max_size);

  Rcpp::Rcout << max_size << "/" << buffer_.size() << ":" << std::string(start, end) << "\n";
  char* outbuf = &buffer_[0];
  size_t inbytesleft = n, outbytesleft = max_size;
  size_t res = Riconv(cd_, &start, &inbytesleft, &outbuf, &outbytesleft);

  if (res == (size_t) -1) {
    switch(errno) {
    case EILSEQ: Rcpp::stop("Invalid multibyte sequence");
    case EINVAL: Rcpp::stop("Incomplete multibyte sequence");
    case E2BIG: Rcpp::stop("Iconv buffer too small");
    default: Rcpp::stop("Iconv failed to convert for unknown reason");
    }
  }

  return Rf_mkCharLenCE(&buffer_[0], max_size - outbytesleft, CE_UTF8);
}
