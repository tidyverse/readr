#ifndef FASTREAD_SOURCE_H_
#define FASTREAD_SOURCE_H_

#include "boost.h"
#include <Rcpp.h>

class Source;
typedef boost::shared_ptr<Source> SourcePtr;

class Source {
public:
  Source(const std::vector<std::string>& comments, std::string encoding)
      : comments_(comments), encoding_(encoding) {}
  virtual ~Source() {}

  virtual const char* begin() const = 0;
  virtual const char* end() const = 0;
  inline std::string encoding() { return encoding_; }

  inline bool has_comments() const { return comments_.size() != 0; }

  const char* skipLines(int skip) {
    bool is_comment = false, lineStart = true;

    const char* pbegin = begin();
    const char* cur = pbegin;
    const char* pend = end();

    while (skip > 0 && cur != pend) {
      if (lineStart) {
        is_comment = has_comments() && isComment(cur);
      }

      if (*cur == '\r') {
        if (cur + 1 != pend && *(cur + 1) == '\n') {
          cur++;
        }
        if (!(is_comment || lineStart))
          skip--;
        lineStart = true;
      } else if (*cur == '\n') {
        if (!(is_comment || lineStart))
          skip--;
        lineStart = true;
      } else if (lineStart) {
        lineStart = false;
      }

      cur++;
    }

    return cur;
  }

  const char* skipBom(const char* begin, const char* end) {

    /* Unicode Byte Order Marks
       https://en.wikipedia.org/wiki/Byte_order_mark#Representations_of_byte_order_marks_by_encoding

       00 00 FE FF: UTF-32BE
       FF FE 00 00: UTF-32LE
       FE FF:       UTF-16BE
       FF FE:       UTF-16LE
       EF BB BF:    UTF-8
   */

    switch (begin[0]) {
    // UTF-32BE
    case '\x00':
      if (end - begin >= 4 && begin[1] == '\x00' && begin[2] == '\xFE' &&
          begin[3] == '\xFF') {
        if (encoding_ == "UTF-32" || encoding_ == "UTF32") {
          encoding_ = "UTF-32BE";
        } else if (encoding_ == "UCS-4" || encoding_ == "UCS4") {
          encoding_ = "UCS-4BE";
        }
        return begin + 4;
      }
      break;

    // UTF-8
    case '\xEF':
      if (end - begin >= 3 && begin[1] == '\xBB' && begin[2] == '\xBF') {
        return begin + 3;
      }
      break;

    // UTF-16BE
    case '\xfe':
      if (end - begin >= 2 && begin[1] == '\xff') {
        if (encoding_ == "UTF-16" || encoding_ == "UTF16") {
          encoding_ = "UTF-16BE";
        } else if (encoding_ == "UCS2" || encoding_ == "UCS-2") {
          encoding_ = "UCS2-BE";
        }
        return begin + 2;
      }
      break;

    case '\xff':
      if (end - begin >= 2 && begin[1] == '\xfe') {

        // UTF-32 LE
        if (end - begin >= 4 && begin[2] == '\x00' && begin[3] == '\x00') {
          if (encoding_ == "UTF-32" || encoding_ == "UTF32") {
            encoding_ = "UTF-32LE";
          } else if (encoding_ == "UCS-4" || encoding_ == "UCS4") {
            encoding_ = "UCS-4LE";
          }
          return begin + 4;
        }

        // UTF-16 LE
        if (encoding_ == "UTF-16" || encoding_ == "UTF16") {
          encoding_ = "UTF-16LE";
        } else if (encoding_ == "UCS2" || encoding_ == "UCS-2") {
          encoding_ = "UCS2-LE";
        }
        return begin + 2;
      }
      break;
    }
    return begin;
  }

  static SourcePtr create(Rcpp::List spec);

  size_t skipCommentAndEmptyLines(const char** cur) const {
    size_t skipped = 0;
    size_t total_skipped = 0;
    while (true) {
      skipped = skipComments(cur);
      skipped += skipEmptyLines(cur);
      total_skipped += skipped;
      if (skipped == 0) {
        return total_skipped;
      }
    }
  }

  size_t skipEmptyLines(const char** cur) const {
    size_t skip = 0;
    const char* theend = end();
    if (*cur == theend) {
      return skip;
    }
    while (*cur != theend && (**cur == '\r' || **cur == '\n')) {
      if (**cur == '\r' && (*cur + 1) != theend && *(*cur + 1) == '\n') {
        ++(*cur);
      }
      ++(*cur);
      ++skip;
    }
    return skip;
  }

  virtual size_t skipComments(const char** cur) const {
    const char* theend = end();
    if (!has_comments()) {
      return 0;
    }
    if (*cur == theend) {
      return 0;
    }
    size_t skip = 0;
    bool another_line = true;
    while (another_line) {
      if ((theend - *cur) % 131072 == 0)
        Rcpp::checkUserInterrupt();
      another_line = false;
      boost::iterator_range<const char*> haystack(*cur, theend);
      for (std::vector<std::string>::const_iterator i = comments_.begin();
           i != comments_.end();
           ++i) {
        if (boost::starts_with(haystack, *i)) {
          while (*cur != theend && **cur != '\r' && **cur != '\n') {
            ++(*cur);
          }
          if (*cur != theend && **cur == '\r' && (*cur + 1) != theend &&
              *(*cur + 1) == '\n') {
            ++(*cur);
          }
          if (**cur == '\n') {
            ++(*cur);
          }
          if (*cur == theend) {
            return skip;
          }
          ++skip;
          another_line = true;
          break; /* for loop */
        }
      }
    }
    return skip;
  }

  bool isComment(const char* cur) const {
    if (!has_comments()) {
      return false;
    }
    boost::iterator_range<const char*> haystack(cur, end());
    for (std::vector<std::string>::const_iterator i = comments_.begin();
         i != comments_.end();
         ++i) {
      if (boost::starts_with(haystack, *i)) {
        return true;
      }
    }
    return false;
  }

private:
  std::vector<std::string> comments_;
  std::string encoding_;
};

#endif
