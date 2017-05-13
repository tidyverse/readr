#include <Rcpp.h>
using namespace Rcpp;
#include "boost.h"

#include <string>

#include "CodePointIterator.h"

static inline bool unicode_is_blank(uint32_t cp) {
  return (
      cp == 0x20 || cp == 0xA0 || cp == 0x1680 ||
      (cp >= 0x2000 && cp < 0x200B) || cp == 0x202F || cp == 0x205F ||
      cp == 0x3000);
}

class CodePointIteratorUTF8 : public CodePointIterator {
public:
  CodePointIteratorUTF8(
      const char* begin, const char* end, std::string encoding, const char* pos)
      : CodePointIterator(begin, end, encoding, pos) {}

private:
  static inline size_t codeUnitSize(const char c) {
    if (isLeadingSingleByte(c))
      return 1;
    if (isLeadingDoubleByte(c))
      return 2;
    if (isLeadingTripleByte(c))
      return 3;
    if (isLeadingQuadByte(c))
      return 4;
    return 0;
  }
  static inline bool isLeadingSingleByte(const char c) {
    return (c & 0x80) == 0x00;
  }
  static inline bool isLeadingDoubleByte(const char c) {
    return (c & 0xE0) == 0xC0;
  }
  static inline bool isLeadingTripleByte(const char c) {
    return (c & 0xF0) == 0xE0;
  }
  static inline bool isLeadingQuadByte(const char c) {
    return (c & 0xF8) == 0xF0;
  }
  static inline bool isContByte(const char c) { return (c & 0xC0) == 0x80; }
  static inline uint32_t get_code_point1(const char c1) {
    return static_cast<uint32_t>(static_cast<unsigned char>(c1));
  };
  static inline uint32_t get_code_point2(const char c1, const char c2) {
    uint32_t u1, u2;
    u1 = static_cast<uint32_t>(static_cast<unsigned char>(c1));
    u2 = static_cast<uint32_t>(static_cast<unsigned char>(c2));
    u1 = u1 & 0x1F;
    u2 = u2 & 0x3F;
    return (u1 << 6) | u2;
  }
  static inline uint32_t
  get_code_point3(const char c1, const char c2, const char c3) {
    uint32_t u1, u2, u3;
    u1 = static_cast<uint32_t>(static_cast<unsigned char>(c1));
    u2 = static_cast<uint32_t>(static_cast<unsigned char>(c2));
    u3 = static_cast<uint32_t>(static_cast<unsigned char>(c3));
    u1 = u1 & 0x0F;
    u2 = u2 & 0x3F;
    u3 = u3 & 0x3F;
    return (u1 << 12) | (u2 << 6) | u3;
  }
  static inline uint32_t
  get_code_point4(const char c1, const char c2, const char c3, const char c4) {
    uint32_t u1, u2, u3, u4;
    u1 = static_cast<uint32_t>(static_cast<unsigned char>(c1));
    u2 = static_cast<uint32_t>(static_cast<unsigned char>(c2));
    u3 = static_cast<uint32_t>(static_cast<unsigned char>(c3));
    u4 = static_cast<uint32_t>(static_cast<unsigned char>(c4));
    u1 = u1 & 0x07;
    u2 = u2 & 0x3F;
    u3 = u3 & 0x3F;
    u4 = u4 & 0x3F;
    return (u1 << 18) | (u2 << 12) | (u3 << 6) | u4;
  }

  size_t get_prev_code_unit_length() const {
    if (p_pos - 1 >= p_end)
      return 0;
    if (p_pos - 1 < p_begin)
      return 0;

    const char* pos = p_pos;
    if (pos <= p_begin)
      return 0;
    size_t len = 0;
    pos--;
    len++;
    while (len <= 5 && pos >= p_begin && isContByte(*pos)) {
      len++;
      pos--;
    }
    if (pos < p_begin) {
      stop("Encoding error. First byte in stream is a UTF-8 continuation byte");
    }
    size_t should_be_length = codeUnitSize(*pos);
    if (should_be_length != len) {
      stop(
          "Encoding error. Leading byte marked %d bytes, found %d",
          should_be_length,
          len);
    }
    return len;
  }

  size_t get_code_unit_length() const {
    if (p_pos == p_end)
      return 0;
    if (p_pos < p_begin)
      return 0;
    const char* pos = p_pos;
    if (isContByte(*pos)) {
      stop("UTF-8 continuation byte in a leading position. Encoding error.");
    }
    if (isLeadingSingleByte(*pos)) {
      return 1;
    }
    if (isLeadingDoubleByte(*pos)) {
      if ((pos + 1 < p_end) && isContByte(*(pos + 1))) {
        return 2;
      } else {
        stop("Invalid 2-byte UTF-8 character at position %d", pos - p_begin);
      }
    }
    if (isLeadingTripleByte(*pos)) {
      if ((pos + 2 < p_end) && isContByte(*(pos + 1)) &&
          isContByte(*(pos + 2))) {
        return 3;
      } else {
        stop("Invalid 3-byte UTF-8 character at position %d", pos - p_begin);
      }
    }
    if (isLeadingQuadByte(*pos)) {
      if ((pos + 3 < p_end) && isContByte(*(pos + 1)) &&
          isContByte(*(pos + 2)) && isContByte(*(pos + 3))) {
        return 4;
      } else {
        stop("Invalid 4-byte UTF-8 character at position %d", pos - p_begin);
      }
    }
    stop("Invalid UTF-8 character at position %d", pos + 1 - p_begin);
  }

  uint32_t get_code_point() const {
    if (p_pos < p_begin || p_pos == p_end)
      return CODEPOINT_ERROR;
    size_t len = get_code_unit_length();
    switch (len) {
    case 1:
      return get_code_point1(*p_pos);
    case 2:
      return get_code_point2(*p_pos, *(p_pos + 1));
    case 3:
      return get_code_point3(*p_pos, *(p_pos + 1), *(p_pos + 2));
    case 4:
      return get_code_point4(*p_pos, *(p_pos + 1), *(p_pos + 2), *(p_pos + 3));
    default:
      return CODEPOINT_ERROR;
    }
  }

  inline bool isblank(uint32_t cp) const { return unicode_is_blank(cp); }
};

template <bool BigEndian>
class CodePointIteratorUCS2 : public CodePointIterator {
public:
  CodePointIteratorUCS2(
      const char* begin, const char* end, std::string encoding, const char* pos)
      : CodePointIterator(begin, end, encoding, pos) {}

private:
  static inline uint32_t get_code_unit(const char c1, const char c2) {
    uint32_t u1, u2;
    u1 = static_cast<uint32_t>(static_cast<unsigned char>(c1));
    u2 = static_cast<uint32_t>(static_cast<unsigned char>(c2));
    if (BigEndian) {
      u1 = (u1 << 8) | u2;
    } else {
      u1 = (u2 << 8) | u1;
    }
    return u1;
  }

  size_t get_prev_code_unit_length() const {
    if (p_pos - 1 >= p_end)
      return 0;
    if (p_pos - 2 < p_begin) {
      return 0;
    }
    return 2;
  }

  size_t get_code_unit_length() const {
    if (p_pos == p_end)
      return 0;
    if (p_pos < p_begin)
      return 0;
    if (p_pos + 1 == p_end) {
      stop("Truncated %s character", p_encoding.c_str());
    }
    uint32_t u1 = get_code_unit(*p_pos, *(p_pos + 1));
    if (u1 > 0xD7FF && u1 < 0xE000) {
      stop("Invalid %s character", p_encoding.c_str());
    }
    return 2;
  }

  uint32_t get_code_point() const {
    if (p_pos < p_begin || p_pos == p_end)
      return CODEPOINT_ERROR;
    return get_code_unit(*p_pos, *(p_pos + 1));
  }

  inline bool isblank(uint32_t cp) const { return unicode_is_blank(cp); }
};

template <bool BigEndian>
class CodePointIteratorUTF16 : public CodePointIterator {
public:
  CodePointIteratorUTF16(
      const char* begin, const char* end, std::string encoding, const char* pos)
      : CodePointIterator(begin, end, encoding, pos) {}

private:
  static inline uint32_t get_code_unitBE(const char c1, const char c2) {
    uint32_t u1, u2;
    u1 = static_cast<uint32_t>(static_cast<unsigned char>(c1));
    u2 = static_cast<uint32_t>(static_cast<unsigned char>(c2));
    u1 = (u1 << 8) | u2;
    return u1;
  }
  static inline uint32_t get_code_unitLE(const char c1, const char c2) {
    uint32_t u1, u2;
    u1 = static_cast<uint32_t>(static_cast<unsigned char>(c1));
    u2 = static_cast<uint32_t>(static_cast<unsigned char>(c2));
    u1 = (u2 << 8) | u1;
    return u1;
  }
  static inline uint32_t get_code_unit(const char c1, const char c2) {
    if (BigEndian) {
      return get_code_unitBE(c1, c2);
    } else {
      return get_code_unitLE(c1, c2);
    }
  }
  static inline uint32_t get_code_pointBE2(const char c1, const char c2) {
    return get_code_unitBE(c1, c2);
  }
  static inline uint32_t get_code_pointBE4(
      const char c1, const char c2, const char c3, const char c4) {
    uint32_t u1 = get_code_unitBE(c1, c2);
    uint32_t u2 = get_code_unitBE(c3, c4);
    return codePointFromSurrogates(u1, u2);
  }
  static inline uint32_t get_code_pointLE2(const char c1, const char c2) {
    return get_code_unitLE(c1, c2);
  }
  static inline uint32_t get_code_pointLE4(
      const char c1, const char c2, const char c3, const char c4) {
    uint32_t u1 = get_code_unitLE(c1, c2);
    uint32_t u2 = get_code_unitLE(c3, c4);
    return codePointFromSurrogates(u1, u2);
  }
  static inline uint32_t get_code_point2(const char c1, const char c2) {
    if (BigEndian) {
      return get_code_pointBE2(c1, c2);
    } else {
      return get_code_pointLE2(c1, c2);
    }
  }
  static inline uint32_t
  get_code_point4(const char c1, const char c2, const char c3, const char c4) {
    if (BigEndian) {
      return get_code_pointBE4(c1, c2, c3, c4);
    } else {
      return get_code_pointLE4(c1, c2, c3, c4);
    }
  }
  static inline bool isBasicMultilingualPlane(uint32_t u1) {
    return (u1 <= 0xD7FF || (u1 >= 0xE000 && u1 <= 0xFFFF));
  }
  static inline bool isHighSurrogate(uint32_t u1) {
    return (u1 >= 0xD800 && u1 <= 0xDBFF);
  }
  static inline bool isLowSurrogate(uint32_t u1) {
    return (u1 >= 0xDC00 && u1 <= 0xDFFF);
  }
  static inline uint32_t codePointFromSurrogates(uint32_t high, uint32_t low) {
    high = high - 0xD800;
    low = low - 0xDC00;
    high = (high << 10) | low;
    high = high + 0x10000;
    return high;
  }

  size_t get_prev_code_unit_length() const {
    uint32_t u1, u2;
    if (p_pos - 2 < p_begin) {
      return 0;
    }
    u2 = get_code_point2((*p_pos - 2), (*p_pos - 1));
    if (isBasicMultilingualPlane(u2)) {
      return 2;
    }
    if (isLowSurrogate(u2)) {
      if (p_pos - 4 < p_begin) {
        return 0;
      }
      u1 = get_code_point2((*p_pos - 4), (*p_pos - 3));
      if (!isHighSurrogate(u1)) {
        stop(
            "Encoding error. Mismatch high/low %s surrogates",
            p_encoding.c_str());
      }
      return 4;
    }
    stop("Invalid UTF16BE character found");
  }

  size_t get_code_unit_length() const {
    if (p_pos + 1 == p_end) {
      stop("Invalid/Truncated %s character", p_encoding.c_str());
    }
    uint32_t u1, u2;
    u1 = get_code_unit(*p_pos, *(p_pos + 1));
    if (isBasicMultilingualPlane(u1)) {
      return 2;
    }
    if (!isHighSurrogate(u1)) {
      stop(
          "Invalid %s character: high surrogate too large", p_encoding.c_str());
    }
    /* Surrogate pair */
    if (p_pos + 3 >= p_end) {
      stop(
          "Invalid/Truncated %s character. Surrogate pair ends too soon",
          p_encoding.c_str());
    }
    u2 = get_code_unit(*(p_pos + 2), *(p_pos + 3));
    if (!isLowSurrogate(u2)) {
      stop(
          "Invalid %s character: low surrogate out of range",
          p_encoding.c_str());
    }
    return 4;
  }

  uint32_t get_code_point() const {
    if (p_pos < p_begin || p_pos == p_end)
      return CODEPOINT_ERROR;
    size_t len = get_code_unit_length();
    if (len == 2) {
      return get_code_point2(*p_pos, *(p_pos + 1));
    } else if (len == 4) {
      return get_code_point4(*p_pos, *(p_pos + 1), *(p_pos + 2), *(p_pos + 3));
    } else {
      return CODEPOINT_ERROR;
    }
  }

  inline bool isblank(uint32_t cp) const { return unicode_is_blank(cp); }
};

template <bool BigEndian>
class CodePointIteratorUTF32 : public CodePointIterator {
public:
  CodePointIteratorUTF32(
      const char* begin, const char* end, std::string encoding, const char* pos)
      : CodePointIterator(begin, end, encoding, pos) {}

private:
  static inline uint32_t
  get_code_pointBE(const char c1, const char c2, const char c3, const char c4) {
    uint32_t u1, u2, u3, u4;
    u1 = static_cast<uint32_t>(static_cast<unsigned char>(c1));
    u2 = static_cast<uint32_t>(static_cast<unsigned char>(c2));
    u3 = static_cast<uint32_t>(static_cast<unsigned char>(c3));
    u4 = static_cast<uint32_t>(static_cast<unsigned char>(c4));
    return (u1 << 24) | (u2 << 16) | (u3 << 8) | u4;
  }
  static inline uint32_t
  get_code_pointLE(const char c1, const char c2, const char c3, const char c4) {
    uint32_t u1, u2, u3, u4;
    u1 = static_cast<uint32_t>(static_cast<unsigned char>(c1));
    u2 = static_cast<uint32_t>(static_cast<unsigned char>(c2));
    u3 = static_cast<uint32_t>(static_cast<unsigned char>(c3));
    u4 = static_cast<uint32_t>(static_cast<unsigned char>(c4));
    return (u4 << 24) | (u3 << 16) | (u2 << 8) | u1;
  }
  size_t get_prev_code_unit_length() const {
    if (p_pos - 1 >= p_end)
      return 0;
    if (p_pos - 1 < p_begin)
      return 0;
    return 4;
  }

  size_t get_code_unit_length() const {
    if (p_pos + 3 >= p_end) {
      stop("Invalid/Truncated %s character", p_encoding.c_str());
    }
    return 4;
  }

  uint32_t get_code_point() const {
    if (p_pos < p_begin || p_pos == p_end)
      return CODEPOINT_ERROR;
    size_t len = get_code_unit_length();
    if (BigEndian) {
      return get_code_pointBE(*p_pos, *(p_pos + 1), *(p_pos + 2), *(p_pos + 3));
    } else {
      return get_code_pointLE(*p_pos, *(p_pos + 1), *(p_pos + 2), *(p_pos + 3));
    }
  }
};

class CodePointIteratorEASCII : public CodePointIterator {
public:
  CodePointIteratorEASCII(
      const char* begin, const char* end, std::string encoding, const char* pos)
      : CodePointIterator(begin, end, encoding, pos) {}

private:
  size_t get_prev_code_unit_length() const {
    if (p_pos - 1 >= p_end)
      return 0;
    if (p_pos - 1 < p_begin)
      return 0;
    return 1;
  }

  size_t get_code_unit_length() const {
    if (p_pos == p_end)
      return 0;
    if (p_pos < p_begin)
      return 0;

    return 1;
  }

  uint32_t get_code_point() const {
    if (p_pos < p_begin || p_pos == p_end)
      return CODEPOINT_ERROR;
    return static_cast<uint32_t>(static_cast<unsigned char>(*p_pos));
  }
};

CodePointIteratorPtr CodePointIterator::create(
    const char* begin, const char* end, std::string encoding, const char* pos) {
  if (encoding == "") {
    stop("Encoding not specified");
  }
  if (encoding == "UTF-16" || encoding == "UTF-32" || encoding == "UCS-2" ||
      encoding == "UCS-4") {
    stop(
        "Specify endianness in encoding as: %sLE or %sBE",
        encoding.c_str(),
        encoding.c_str());
  }

  if (encoding == "UTF-8" || encoding == "UTF8") {
    return CodePointIteratorPtr(
        new CodePointIteratorUTF8(begin, end, encoding, pos));
  } else if (encoding == "UCS2-BE" || encoding == "UCS2BE") {
    return CodePointIteratorPtr(
        new CodePointIteratorUCS2<true>(begin, end, encoding, pos));
  } else if (encoding == "UCS2-LE" || encoding == "UCS2LE") {
    return CodePointIteratorPtr(
        new CodePointIteratorUCS2<false>(begin, end, encoding, pos));
  } else if (encoding == "UTF16-LE" || encoding == "UTF16LE") {
    return CodePointIteratorPtr(
        new CodePointIteratorUTF16<false>(begin, end, encoding, pos));
  } else if (encoding == "UTF16-BE" || encoding == "UTF16BE") {
    return CodePointIteratorPtr(
        new CodePointIteratorUTF16<true>(begin, end, encoding, pos));
  } else if (
      encoding == "UTF32-BE" || encoding == "UTF32BE" ||
      encoding == "UCS-4BE") {
    return CodePointIteratorPtr(
        new CodePointIteratorUTF32<true>(begin, end, encoding, pos));
  } else if (
      encoding == "UTF32-LE" || encoding == "UTF32LE" ||
      encoding == "UCS-4LE") {
    return CodePointIteratorPtr(
        new CodePointIteratorUTF32<false>(begin, end, encoding, pos));
  } else {
    /* TO DO: Big5 and ShiftJIS? */
    return CodePointIteratorPtr(
        new CodePointIteratorEASCII(begin, end, encoding, pos));
  }
}
