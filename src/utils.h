#ifndef FASTREAD_UTILS_H_
#define FASTREAD_UTILS_H_

// Advances iterator if the next character is a LF.
// Returns iterator to end of line.
template <class Iter>
inline Iter advanceForLF(Iter* pBegin, Iter end) {
  Iter cur = *pBegin;
  if (*cur == '\r' && (cur + 1 != end) && *(cur + 1) == '\n')
    (*pBegin)++;

  return cur;
}

#endif
