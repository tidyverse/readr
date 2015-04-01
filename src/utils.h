
template <class Iter>
inline Iter advanceForLF(Iter* pBegin, Iter end) {
  Iter cur = *pBegin;
  if (*cur == '\r' && (cur + 1 != end) && *(cur + 1) == '\n')
    (*pBegin)++;

  return cur;
}
