#ifndef FASTREAD_UTILS_H_
#define FASTREAD_UTILS_H_

#include <cstring>
#include <locale>
#include <string>

// Advances iterator if the next character is a LF.
// Returns iterator to end of line.
template <class Iter> inline Iter advanceForLF(Iter* pBegin, Iter end) {
  Iter cur = *pBegin;
  if (cur == end) {
    return cur;
  }
  if (*cur == '\r' && (cur + 1 != end) && *(cur + 1) == '\n')
    (*pBegin)++;

  return cur;
}

const static char* const true_values[] = {
    "T", "t", "True", "TRUE", "true", (char*)NULL};
const static char* const false_values[] = {
    "F", "f", "False", "FALSE", "false", (char*)NULL};

inline bool isTrue(const char* start, const char* end) {
  size_t len = end - start;

  for (int i = 0; true_values[i]; i++) {
    size_t true_len = strlen(true_values[i]);
    if (true_len == len && strncmp(start, true_values[i], len) == 0) {
      return true;
    }
  }
  return false;
}
inline bool isFalse(const char* start, const char* end) {
  size_t len = end - start;

  for (int i = 0; false_values[i]; i++) {
    if (strlen(false_values[i]) == len &&
        strncmp(start, false_values[i], len) == 0) {
      return true;
    }
  }
  return false;
}

inline bool isLogical(const char* start, const char* end) {
  return isTrue(start, end) || isFalse(start, end);
}

inline bool istarts_with(const std::string& input, const std::string& test) {
  if (test.size() > input.size()) {
    return false;
  }

  auto test_it = test.cbegin();
  auto input_it = input.cbegin();
  auto test_end = test.cend();
  auto locale = std::locale();
  while (test_it != test_end) {
    if (std::toupper(*test_it++, locale) != std::toupper(*input_it++, locale)) {
      return false;
    }
  }
  return true;
}

inline bool starts_with_comment(
    const char* cur, const char* end, const std::string& comment) {
  // If the comment is bigger than what we are testing, it cannot start with it.
  if ((long)comment.size() > (end - cur)) {
    return false;
  }
  for (auto c : comment) {
    if (*cur++ != c) {
      return false;
    }
  }
  return true;
}

#endif
