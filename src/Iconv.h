#ifndef READ_ICONV_H_
#define READ_ICONV_H_

#include <iconv.h>
#include <errno.h>

class Iconv {
  iconv_t cd_;
  std::string buffer_;

public:

  Iconv(const std::string& from, const std::string& to = "UTF-8") {
    cd_ = iconv_open(to.c_str(), from.c_str());

    if (cd_ == (iconv_t) -1) {
      if (errno == EINVAL) {
        Rcpp::stop("Can't convert from %s to %s", from, to);
      } else {
        Rcpp::stop("Iconv initialisation failed");
      }
    }

    // Allocate space in buffer
    buffer_.resize(1024);
  }

  ~Iconv() {
    iconv_close(cd_);
  }

  std::string convert(std::string from) {
    size_t max_size = from.size() * 4;
    if (from.size() < max_size)
      buffer_.resize(max_size);

    // http://man7.org/linux/man-pages/man3/iconv.3.html
    char* inbuf = &from[0];
    char* outbuf = &buffer_[0];
    size_t inbytesleft = from.size(), outbytesleft = max_size;
    size_t res = iconv(cd_, &inbuf, &inbytesleft, &outbuf, &outbytesleft);

    if (res == (size_t) -1) {
      switch(errno) {
      case EILSEQ: Rcpp::stop("Invalid multibyte sequence");
      case EINVAL: Rcpp::stop("Incomplete multibyte sequence");
      case E2BIG: Rcpp::stop("Iconv buffer too small");
      default: Rcpp::stop("Iconv failed to convert for unknown reason");
      }
    }

    return std::string(&buffer_[0], outbuf);
  }

};

#endif
