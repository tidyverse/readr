#ifndef FASTREAD_UTILS_H_
#define FASTREAD_UTILS_H_

#include <string.h>

#include <boost/range/algorithm/equal.hpp>

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

#endif
