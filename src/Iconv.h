#ifndef READ_ICONV_H_
#define READ_ICONV_H_

#include "R_ext/Riconv.h"
#include <errno.h>

class Iconv {
  void* cd_;
  std::string buffer_;

public:
  Iconv() {
    cd_ = NULL;
  }

  Iconv(const std::string& from, const std::string& to = "UTF-8") {
    if (from == "UTF-8") {
      cd_ = NULL;
    } else {
      cd_ = Riconv_open(to.c_str(), from.c_str());
      if (cd_ == (void*) -1) {
        if (errno == EINVAL) {
          Rcpp::stop("Can't convert from %s to %s", from, to);
        } else {
          Rcpp::stop("Iconv initialisation failed");
        }
      }

      // Allocate space in buffer
      buffer_.resize(1024);
    }

  }

  ~Iconv() {
    if (cd_ != NULL)
      Riconv_close(cd_);
  }

  SEXP makeSEXP(const char* start, const char* end);
};

#endif
