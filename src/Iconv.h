#ifndef READ_ICONV_H_
#define READ_ICONV_H_

#include "R_ext/Riconv.h"
#include <errno.h>
#include <string.h>

class Iconv {
  void* cd_;
  std::string buffer_;

public:
  Iconv(const std::string& from = "UTF-8", const std::string& to = "UTF-8");
  virtual ~Iconv();
  std::string from;
  std::string to;

  SEXP makeSEXP(const char* start, const char* end, bool hasNull = true);
  std::string makeString(const char* start, const char* end);
  std::string makeString(const std::string& what);

  /* Use only if `what` is a Cstring (strlen works, zero byte marks the end) */
  std::string makeString(const char* what);

  static std::string encode(SEXP what, std::string encoding) {
    cetype_t what_encoding = Rf_getCharCE(what);
    std::string what_encoding_str;
    if (what_encoding == CE_UTF8) {
      what_encoding_str = "UTF-8";
    } else if (what_encoding == CE_LATIN1) {
      what_encoding_str = "latin1";
    } else if (what_encoding == CE_NATIVE) {
      what_encoding_str = "";
    } else {
      //what_encoding_str = "bytes";
      return Rcpp::as<std::string>(what);
    }
    Iconv encoder(what_encoding_str, encoding);
    return encoder.makeString(Rcpp::as<std::string>(what));
  }

private:
  // Returns number of characters in buffer
  size_t convert(const char* start, const char* end);
};

#endif
