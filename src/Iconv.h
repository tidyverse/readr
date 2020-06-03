#ifndef READ_ICONV_H_
#define READ_ICONV_H_

#include "cpp11/R.hpp"
#include <string>

#include "R_ext/Riconv.h"
#include <errno.h>

class Iconv {
  void* cd_;
  std::string buffer_;

public:
  Iconv(const std::string& from, const std::string& to = "UTF-8");
  virtual ~Iconv();

  SEXP makeSEXP(const char* start, const char* end, bool hasNull = true);
  std::string makeString(const char* start, const char* end);

private:
  // Returns number of characters in buffer
  size_t convert(const char* start, const char* end);
};

#endif
