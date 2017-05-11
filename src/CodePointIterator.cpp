#include <Rcpp.h>
using namespace Rcpp;
#include "boost.h"

#include <string>

#include "CodePointIterator.h"

class UTF8Validator {
public:
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
  static inline uint32_t get_code_point(const char c1) {
    return static_cast<uint32_t>(static_cast<unsigned char>(c1));
  };
  static inline uint32_t get_code_point(const char c1, const char c2) {
    uint32_t u1, u2;
    u1 = static_cast<uint32_t>(static_cast<unsigned char>(c1));
    u2 = static_cast<uint32_t>(static_cast<unsigned char>(c2));
    u1 = u1 & 0x1F;
    u2 = u2 & 0x3F;
    return (u1 << 6) | u2;
  }
  static inline uint32_t
  get_code_point(const char c1, const char c2, const char c3) {
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
  get_code_point(const char c1, const char c2, const char c3, const char c4) {
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
};

class UTF16Validator {
public:
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
  static inline uint32_t get_code_pointBE(const char c1, const char c2) {
    return get_code_unitBE(c1, c2);
  }
  static inline uint32_t
  get_code_pointBE(const char c1, const char c2, const char c3, const char c4) {
    uint32_t u1 = get_code_unitBE(c1, c2);
    uint32_t u2 = get_code_unitBE(c3, c4);
    return codePointFromSurrogates(u1, u2);
  }
  static inline uint32_t get_code_pointLE(const char c1, const char c2) {
    return get_code_unitLE(c1, c2);
  }
  static inline uint32_t
  get_code_pointLE(const char c1, const char c2, const char c3, const char c4) {
    uint32_t u1 = get_code_unitLE(c1, c2);
    uint32_t u2 = get_code_unitLE(c3, c4);
    return codePointFromSurrogates(u1, u2);
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
};

class UTF32Validator {
public:
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
};

class UCS2Validator {
public:
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
};

size_t CodePointIterator::get_prev_code_unit_length() const {
  if (p_pos - 1 >= p_end)
    return 0;
  if (p_pos - 1 < p_begin)
    return 0;

  if (p_encoding == "UTF-8" || p_encoding == "UTF8") {
    const char* pos = p_pos;
    if (pos <= p_begin)
      return 0;
    size_t len = 0;
    pos--;
    len++;
    while (len <= 5 && pos >= p_begin && UTF8Validator::isContByte(*pos)) {
      len++;
      pos--;
    }
    if (pos < p_begin) {
      stop("Encoding error. First byte in stream is a UTF-8 continuation byte");
    }
    size_t should_be_length = UTF8Validator::codeUnitSize(*pos);
    if (should_be_length != len) {
      stop(
          "Encoding error. Leading byte marked %d bytes, found %d",
          should_be_length,
          len);
    }
    return len;
  } else if (p_encoding == "UCS-2BE" || p_encoding == "UCS-2LE") {
    if (p_pos - 2 < p_begin) {
      return 0;
    }
    return 2;
  } else if (p_encoding == "UTF-16BE" || p_encoding == "UTF16BE") {
    uint32_t u1, u2;
    if (p_pos - 2 < p_begin) {
      return 0;
    }
    u2 = UTF16Validator::get_code_pointBE((*p_pos - 2), (*p_pos - 1));
    if (UTF16Validator::isBasicMultilingualPlane(u2)) {
      return 2;
    }
    if (UTF16Validator::isLowSurrogate(u2)) {
      if (p_pos - 4 < p_begin) {
        return 0;
      }
      u1 = UTF16Validator::get_code_pointBE((*p_pos - 4), (*p_pos - 3));
      if (!UTF16Validator::isHighSurrogate(u1)) {
        stop("Encoding error. Mismatch high/low UTF16BE surrogates");
      }
      return 4;
    }
    stop("Invalid UTF16BE character found");
  } else if (p_encoding == "UTF-16LE" || p_encoding == "UTF16LE") {
    uint32_t u1, u2;
    if (p_pos - 2 < p_begin) {
      return 0;
    }
    u2 = UTF16Validator::get_code_pointLE((*p_pos - 2), (*p_pos - 1));
    if (UTF16Validator::isBasicMultilingualPlane(u2)) {
      return 2;
    }
    if (UTF16Validator::isLowSurrogate(u2)) {
      if (p_pos - 4 < p_begin) {
        return 0;
      }
      u1 = UTF16Validator::get_code_pointLE((*p_pos - 4), (*p_pos - 3));
      if (!UTF16Validator::isHighSurrogate(u1)) {
        stop("Encoding error. Mismatch high/low UTF16LE surrogates");
      }
      return 4;
    }
    stop("Invalid UTF16LE character found");
  } else if (
      p_encoding == "UCS4" || p_encoding == "UCS-4" ||
      p_encoding == "UCS-4BE" || p_encoding == "UCS-4LE" ||
      p_encoding == "UTF32" || p_encoding == "UTF-32" ||
      p_encoding == "UTF-32BE" || p_encoding == "UTF-32LE" ||
      p_encoding == "UTF32BE" || p_encoding == "UTF32LE") {
    return 4;
  } else {
    /* For most cases (latin-1...) this is true, FIXME: Big5 and ShiftJIS are
     * not yet contemplated */
    return 1;
  }
}

size_t CodePointIterator::get_code_unit_length() const {
  if (p_pos == p_end)
    return 0;
  if (p_pos < p_begin)
    return 0;

  if (p_encoding == "UTF-8" || p_encoding == "UTF8") {
    const char* pos = p_pos;
    if (UTF8Validator::isContByte(*pos)) {
      stop("UTF-8 continuation byte in a leading position. Encoding error.");
    }
    if (UTF8Validator::isLeadingSingleByte(*pos)) {
      return 1;
    }
    if (UTF8Validator::isLeadingDoubleByte(*pos)) {
      if ((pos + 1 < p_end) && UTF8Validator::isContByte(*(pos + 1))) {
        return 2;
      } else {
        stop("Invalid 2-byte UTF-8 character at position %d", pos - p_begin);
      }
    }
    if (UTF8Validator::isLeadingTripleByte(*pos)) {
      if ((pos + 2 < p_end) && UTF8Validator::isContByte(*(pos + 1)) &&
          UTF8Validator::isContByte(*(pos + 2))) {
        return 3;
      } else {
        stop("Invalid 3-byte UTF-8 character at position %d", pos - p_begin);
      }
    }
    if (UTF8Validator::isLeadingQuadByte(*pos)) {
      if ((pos + 3 < p_end) && UTF8Validator::isContByte(*(pos + 1)) &&
          UTF8Validator::isContByte(*(pos + 2)) &&
          UTF8Validator::isContByte(*(pos + 3))) {
        return 4;
      } else {
        stop("Invalid 4-byte UTF-8 character at position %d", pos - p_begin);
      }
    }
    stop("Invalid UTF-8 character at position %d", pos + 1 - p_begin);
  } else if (p_encoding == "UCS-2BE") {
    if (p_pos + 1 == p_end) {
      stop("Truncated %s character", p_encoding.c_str());
    }
    uint32_t u1 = UCS2Validator::get_code_unitBE(*p_pos, *(p_pos + 1));
    if (u1 > 0xD7FF && u1 < 0xE000) {
      stop("Invalid %s character", p_encoding.c_str());
    }
    return 2;
  } else if (p_encoding == "UCS-2LE") {
    if (p_pos + 1 == p_end) {
      stop("Truncated %s character", p_encoding.c_str());
    }
    uint32_t u1 = UCS2Validator::get_code_unitLE(*p_pos, *(p_pos + 1));
    if (u1 > 0xD7FF && u1 < 0xE000) {
      stop("Invalid %s character", p_encoding.c_str());
    }
    return 2;
  } else if (p_encoding == "UTF-16BE" || p_encoding == "UTF16BE") {
    if (p_pos + 1 == p_end) {
      stop("Invalid/Truncated %s character", p_encoding.c_str());
    }
    uint32_t u1, u2;
    u1 = UTF16Validator::get_code_unitBE(*p_pos, *(p_pos + 1));
    if (UTF16Validator::isBasicMultilingualPlane(u1)) {
      return 2;
    }
    if (!UTF16Validator::isHighSurrogate(u1)) {
      stop(
          "Invalid %s character: high surrogate too large", p_encoding.c_str());
    }
    /* Surrogate pair */
    if (p_pos + 3 >= p_end) {
      stop(
          "Invalid/Truncated %s character. Surrogate pair ends too soon",
          p_encoding.c_str());
    }
    u2 = UTF16Validator::get_code_unitBE(*(p_pos + 2), *(p_pos + 3));
    if (!UTF16Validator::isLowSurrogate(u2)) {
      stop(
          "Invalid %s character: low surrogate out of range",
          p_encoding.c_str());
    }
    return 4;
  } else if (p_encoding == "UTF-16LE" || p_encoding == "UTF16LE") {
    if (p_pos + 1 == p_end) {
      stop(
          "Invalid/Truncated %s character. Missing second byte of UTF-16LE "
          "code unit.",
          p_encoding.c_str());
    }
    uint32_t u1, u2;
    u1 = UTF16Validator::get_code_unitLE(*p_pos, *(p_pos + 1));

    if (UTF16Validator::isBasicMultilingualPlane(u1)) {
      return 2;
    }

    if (!UTF16Validator::isHighSurrogate(u1)) {
      stop(
          "Invalid %s character: high surrogate too large", p_encoding.c_str());
    }

    /* Surrogate pair */

    if (p_pos + 3 >= p_end) {
      stop(
          "Invalid/Truncated %s character. Surrogate pair ends too soon",
          p_encoding.c_str());
    }

    u2 = UTF16Validator::get_code_unitLE(*(p_pos + 2), *(p_pos + 3));
    if (!UTF16Validator::isLowSurrogate(u2)) {
      stop(
          "Invalid %s character: low surrogate out of range",
          p_encoding.c_str());
    }
    return 4;
  } else if (
      p_encoding == "UCS4" || p_encoding == "UCS-4" ||
      p_encoding == "UCS-4BE" || p_encoding == "UCS-4LE" ||
      p_encoding == "UTF32" || p_encoding == "UTF-32" ||
      p_encoding == "UTF-32BE" || p_encoding == "UTF-32LE" ||
      p_encoding == "UTF32BE" || p_encoding == "UTF32LE") {
    if (p_pos + 3 >= p_end) {
      stop("Invalid/Truncated %s character", p_encoding.c_str());
    }
    return 4;
  } else {
    return 1;
  }
}

uint32_t CodePointIterator::get_code_point() const {
  if (p_pos < p_begin || p_pos == p_end)
    return CODEPOINT_ERROR;
  size_t len = get_code_unit_length();
  if (p_encoding == "UTF-8" || p_encoding == "UTF8") {
    switch (len) {
    case 1:
      return UTF8Validator::get_code_point(*p_pos);
    case 2:
      return UTF8Validator::get_code_point(*p_pos, *(p_pos + 1));
    case 3:
      return UTF8Validator::get_code_point(*p_pos, *(p_pos + 1), *(p_pos + 2));
    case 4:
      return UTF8Validator::get_code_point(
          *p_pos, *(p_pos + 1), *(p_pos + 2), *(p_pos + 3));
    default:
      return CODEPOINT_ERROR;
    }
  } else if (p_encoding == "UCS-2BE") {
    return UCS2Validator::get_code_unitBE(*p_pos, *(p_pos + 1));
  } else if (p_encoding == "UCS-2LE") {
    return UCS2Validator::get_code_unitLE(*p_pos, *(p_pos + 1));
  } else if (p_encoding == "UTF-16BE" || p_encoding == "UTF16BE") {
    if (len == 2) {
      return UTF16Validator::get_code_pointBE(*p_pos, *(p_pos + 1));
    } else if (len == 4) {
      return UTF16Validator::get_code_pointBE(
          *p_pos, *(p_pos + 1), *(p_pos + 2), *(p_pos + 3));
    } else {
      return CODEPOINT_ERROR;
    }
  } else if (p_encoding == "UTF-16LE" || p_encoding == "UTF16LE") {
    if (len == 2) {
      return UTF16Validator::get_code_pointLE(*p_pos, *(p_pos + 1));
    } else if (len == 4) {
      return UTF16Validator::get_code_pointLE(
          *p_pos, *(p_pos + 1), *(p_pos + 2), *(p_pos + 3));
    } else {
      return CODEPOINT_ERROR;
    }
  } else if (
      p_encoding == "UCS-4BE" || p_encoding == "UTF-32BE" ||
      p_encoding == "UTF32BE") {
    return UTF32Validator::get_code_pointBE(
        *p_pos, *(p_pos + 1), *(p_pos + 2), *(p_pos + 3));
  } else if (
      p_encoding == "UCS-4LE" || p_encoding == "UTF-32LE" ||
      p_encoding == "UTF32LE") {
    return UTF32Validator::get_code_pointLE(
        *p_pos, *(p_pos + 1), *(p_pos + 2), *(p_pos + 3));
  } else {
    return static_cast<uint32_t>(static_cast<unsigned char>(*p_pos));
  }
}
