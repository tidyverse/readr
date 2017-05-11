#ifndef FASTREAD_CODEUNITITERATOR_H_
#define FASTREAD_CODEUNITITERATOR_H_

#include <Rcpp.h>
using namespace Rcpp;
#include "boost.h"
#include <boost/cstdint.hpp>

#include <string>
#include <iterator>

class CodePointIterator : public std::iterator<std::bidirectional_iterator_tag, uint32_t> {
public:
  inline size_t bytes_passed() const {
    return get_pos() - get_begin();
  }

  inline size_t bytes_total() const {
    return get_end() - get_begin();
  }

  static size_t code_points_between(const char *begin, const char *end, std::string encoding) {
    CodePointIterator tmp(begin, end, encoding);
    size_t out = 0;
    while (!tmp.is_end()) {
      ++tmp;
      ++out;
    }
    return out;
  }

  static const uint32_t CODEPOINT_ERROR = 0xFFFFFFFF;
  CodePointIterator(const char *begin, const char *end, std::string encoding,
                    const char *pos = 0) : p_encoding(encoding),
                    p_pos(pos == 0 ? begin : pos),
                    p_begin(begin),
                    p_end(end) {
    if (encoding == "") {
      stop("Encoding not specified");
    }
    if (encoding == "UTF-16" || encoding == "UTF-32" || encoding == "UCS-2" || encoding == "UCS-4") {
      stop("Specify endianness in encoding as: %sLE or %sBE", encoding.c_str(), encoding.c_str());
    }
  };

  CodePointIterator(const CodePointIterator &obj) {
    p_begin = obj.p_begin;
    p_pos = obj.p_pos;
    p_end = obj.p_end;
    p_encoding = obj.p_encoding;
  }

  CodePointIterator() : p_begin(NULL), p_pos(NULL), p_end(NULL), p_encoding() {}

  CodePointIterator begin() {
    return CodePointIterator(p_begin, p_end, p_encoding, p_begin);
  }

  CodePointIterator end() {
    return CodePointIterator(p_begin, p_end, p_encoding, p_end);
  }

  bool is_begin() const {
    return (p_pos == p_begin);
  }

  bool is_end() const {
    return (p_pos == p_end);
  }

  bool operator==(CodePointIterator const& rhs) const {
    return (p_pos == rhs.p_pos);
  }

  bool operator!=(CodePointIterator const& rhs) const {
    return !(*this==rhs);
  }

  CodePointIterator& operator++() {
    size_t point_size = get_code_unit_length();
    if (p_pos + point_size > p_end) {
      stop("Advancing goes past the end");
    }
    p_pos += point_size;
    return *this;
  }

  CodePointIterator operator++(int) {
    CodePointIterator tmp (*this);
    ++(*this);
    return tmp;
  }

  CodePointIterator& operator--() {
    size_t point_size = get_prev_code_unit_length();
    if (p_pos - point_size < p_begin) {
      stop("Going back before the beginning");
    }
    p_pos -= point_size;
    return *this;
  }

  CodePointIterator operator--(int) {
    CodePointIterator tmp (*this);
    --(*this);
    return tmp;
  }

  const char * get_begin() const {
    return p_begin;
  }

  const char * get_pos() const {
    return p_pos;
  }

  const char * get_end() const {
    return p_end;
  }

  uint32_t operator* () const {
    return get_code_point();
  }

  CodePointIterator operator+ (int i) {
    CodePointIterator tmp(*this);
    if (i > 0) {
      for (int j=0; j<i;++j) {
        ++tmp;
      }
    } else if (i < 0) {
      for (int j=0; j<-i;++j) {
        --tmp;
      }
    }
    return tmp;
  }

  CodePointIterator operator- (int i) {
    CodePointIterator tmp(*this);
    if (i > 0) {
      for (int j=0; j<i;++j) {
        --tmp;
      }
    } else if (i < 0) {
      for (int j=0; j<-i;++j) {
        ++tmp;
      }
    }
    return tmp;
  }

  /* For most encodings (UTF-8, UTF-16, UTF-32, latin1...), the code points are
     ascii-compatible. Even for encodings like UTF-16, where ASCII characters are
     represented as code units of 2 bytes, the code point that represents those
     code units is Unicode and the unicode numbering starts like the ASCII.

     However, there are some encodings (e.g. CP1026, that is EBCDIC based) where
     there is not ASCII compatibility. If you want to add support to those encodings
     you just need to modify these cp_* functions.
  */
  inline uint32_t cp_null() const {
    return 0x00;
  }

  inline uint32_t cp_alert() const {
    return 0x07;
  }

  inline uint32_t cp_backspace() const {
    if (p_encoding == "CP1026") {
      return 0x16;
    }
    return 0x08;
  }

  inline uint32_t cp_htab() const {
    if (p_encoding == "CP1026") {
      return 0x05;
    }
    return 0x09;
  }

  inline uint32_t cp_lf() const {
    if (p_encoding == "CP1026") {
      return 0x25;
    }
    return 0x0A;
  }

  inline uint32_t cp_vtab() const {
    return 0x0B;
  }

  inline uint32_t cp_formfeed() const {
    return 0x0C;
  }

  inline uint32_t cp_cr() const {
    return 0x0D;
  }

  inline uint32_t cp_space() const {
    if (p_encoding == "CP1026") {
      return 0x40;
    }
    return 0x20;
  }

  inline uint32_t cp_quotation_mark() const {
    if (p_encoding == "CP1026") {
      return 0xFC;
    }
    return 0x22;
  }

  inline uint32_t cp_left_square_bracket() const {
    if (p_encoding == "CP1026") {
      return 0x68;
    }
    return 0x5B;
  }

  inline uint32_t cp_backslash() const {
    if (p_encoding == "CP1026") {
      return 0xDC;
    }
    return 0x5C;
  }

  inline uint32_t cp_right_square_bracket() const {
    if (p_encoding == "CP1026") {
      return 0xAC;
    }
    return 0x5D;
  }

  inline bool isblank(uint32_t cp) const {
    return cp == cp_htab() || cp ==  cp_space();
  }

  inline bool isspace(uint32_t cp) const {
    return cp == cp_htab() || cp ==  cp_space() || cp == cp_lf() ||
      cp == cp_cr() || cp == cp_formfeed() || cp == cp_vtab();
  }

  boost::iterator_range<const char*> get_iterator_range() const {
    boost::iterator_range<const char*> haystack(p_pos, p_end);
    return haystack;
  }

  void advance_until_crlf() {
    uint32_t cr = cp_cr();
    uint32_t lf = cp_lf();
    uint32_t unit;
    for (;!is_end(); ++(*this)) {
      unit = this->get_code_point();
      if (unit == cr || unit == lf) {
        break;
      }
    }
    return;
  }

  void advance_if_crlf() {
    if ( this->get_code_point() == cp_cr() &&
         !((*this + 1).is_end()) &&
         *((*this) + 1) == cp_lf()) {
      ++(*this);
    }
  }

private:
  const char* p_pos;
  const char *p_begin;
  const char *p_end;
  std::string p_encoding;

  size_t get_prev_code_unit_length() const;
  size_t get_code_unit_length() const;
  uint32_t get_code_point() const;
};

#endif
