#ifndef FASTREAD_CODEUNITITERATOR_H_
#define FASTREAD_CODEUNITITERATOR_H_

#include <Rcpp.h>
using namespace Rcpp;
#include "boost.h"
#include <boost/cstdint.hpp>

#include <iterator>
#include <string>

class CodePointIterator;
typedef boost::shared_ptr<CodePointIterator> CodePointIteratorPtr;

class CodePointIterator
    : public std::iterator<std::bidirectional_iterator_tag, uint32_t> {
public:
  inline size_t bytes_passed() const { return get_pos() - get_begin(); }

  inline size_t bytes_total() const { return get_end() - get_begin(); }

  static size_t code_points_between(
      const char* begin, const char* end, std::string encoding) {
    CodePointIteratorPtr tmp = create(begin, end, encoding);
    size_t out = 0;
    while (!tmp->is_end()) {
      tmp->next();
      ++out;
    }
    return out;
  }

  static const uint32_t CODEPOINT_ERROR = 0xFFFFFFFF;
  CodePointIterator(
      const char* begin,
      const char* end,
      std::string encoding,
      const char* pos = 0)
      : p_pos(pos == 0 ? begin : pos),
        p_begin(begin),
        p_end(end),
        p_encoding(encoding){};

  CodePointIterator(const CodePointIterator& obj) {
    p_begin = obj.p_begin;
    p_pos = obj.p_pos;
    p_end = obj.p_end;
    p_encoding = obj.p_encoding;
  }

  CodePointIterator() : p_pos(NULL), p_begin(NULL), p_end(NULL), p_encoding() {}

  bool is_begin() const { return (p_pos == p_begin); }

  bool is_end() const { return (p_pos == p_end); }

  bool operator==(CodePointIterator const& rhs) const {
    return (p_pos == rhs.p_pos);
  }

  bool operator!=(CodePointIterator const& rhs) const {
    return !(*this == rhs);
  }

  void next() {
    size_t point_size = get_code_unit_length();
    if (p_pos + point_size > p_end) {
      stop("Advancing goes past the end");
    }
    p_pos += point_size;
  }

  CodePointIterator& operator++() {
    this->next();
    return *this;
  }

  CodePointIteratorPtr operator++(int) {
    CodePointIteratorPtr tmp = create(*this);
    this->next();
    return tmp;
  }

  void prev() {
    size_t point_size = get_prev_code_unit_length();
    if (p_pos - point_size < p_begin) {
      stop("Going back before the beginning");
    }
    p_pos -= point_size;
  }

  CodePointIterator& operator--() {
    this->prev();
    return *this;
  }

  CodePointIteratorPtr operator--(int) {
    CodePointIteratorPtr tmp = create(*this);
    this->prev();
    return tmp;
  }

  const char* get_begin() const { return p_begin; }

  const char* get_pos() const { return p_pos; }

  const char* get_end() const { return p_end; }

  uint32_t cp() const { return get_code_point(); }
  uint32_t operator*() const { return cp(); }

  static CodePointIteratorPtr shift(const CodePointIterator* pt, int offset) {
    CodePointIteratorPtr tmp = create(*pt);
    if (offset > 0) {
      for (int j = 0; j < offset; ++j) {
        tmp->next();
      }
    } else if (offset < 0) {
      for (int j = 0; j < -offset; ++j) {
        tmp->prev();
      }
    }
    return tmp;
  }

  CodePointIteratorPtr operator+(int i) { return shift(this, i); }

  CodePointIteratorPtr operator-(int i) {
    CodePointIteratorPtr tmp = create(*this);
    if (i > 0) {
      for (int j = 0; j < i; ++j) {
        tmp->prev();
      }
    } else if (i < 0) {
      for (int j = 0; j < -i; ++j) {
        tmp->next();
      }
    }
    return tmp;
  }

  /* For most encodings (UTF-8, UTF-16, UTF-32, latin1...), the code points are
     ascii-compatible. Even for encodings like UTF-16, where ASCII characters
     are represented as code units of 2 bytes, the code point that represents
     those
     code units is Unicode and the unicode numbering starts like the ASCII.

     However, there are some encodings (e.g. CP1026, that is EBCDIC based) where
     there is not ASCII compatibility. If you want to add support to those
     encodings you just need to modify these cp_* functions, or make them
     virtual
     and edit the inherited function.
  */
  static inline uint32_t cp_null() { return 0x00; }

  static inline uint32_t cp_alert() { return 0x07; }

  static inline uint32_t cp_backspace() { return 0x08; }

  static inline uint32_t cp_htab() { return 0x09; }

  static inline uint32_t cp_lf() { return 0x0A; }

  static inline uint32_t cp_vtab() { return 0x0B; }

  static inline uint32_t cp_formfeed() { return 0x0C; }

  static inline uint32_t cp_cr() { return 0x0D; }

  static inline uint32_t cp_space() { return 0x20; }

  static inline uint32_t cp_quotation_mark() { return 0x22; }

  static inline uint32_t cp_left_square_bracket() { return 0x5B; }

  static inline uint32_t cp_backslash() { return 0x5C; }

  static inline uint32_t cp_right_square_bracket() { return 0x5D; }

  virtual inline bool isblank(uint32_t cp) const {
    return cp == cp_htab() || cp == cp_space();
  }

  inline bool isspace(uint32_t cp) const {
    return cp == cp_htab() || cp == cp_space() || cp == cp_lf() ||
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
    for (; !is_end(); next()) {
      unit = this->cp();
      if (unit == cr || unit == lf) {
        break;
      }
    }
    return;
  }

  void advance_if_crlf() {
    if (this->get_code_point() == cp_cr() && !((*this + 1)->is_end()) &&
        ((*this) + 1)->cp() == cp_lf()) {
      this->next();
    }
  }

  static CodePointIteratorPtr create(const CodePointIterator& obj) {
    return CodePointIterator::create(
        obj.p_begin, obj.p_end, obj.p_encoding, obj.p_pos);
  }

  static CodePointIteratorPtr create(
      const char* begin,
      const char* end,
      std::string encoding,
      const char* pos = 0);

protected:
  const char* p_pos;
  const char* p_begin;
  const char* p_end;
  std::string p_encoding;

private:
  virtual size_t get_prev_code_unit_length() const = 0;
  virtual size_t get_code_unit_length() const = 0;
  virtual uint32_t get_code_point() const = 0;
};

#endif
