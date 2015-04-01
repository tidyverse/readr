#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "Tokenizer.h"
#include "utils.h"

std::vector<bool> emptyCols_(SourceIterator begin, SourceIterator end, size_t n = 100) {

  std::vector<bool> is_white;

  size_t row = 0, col = 0;
  for (SourceIterator cur = begin; cur != end; ++cur) {
    if (row > n)
      break;

    switch(*cur) {
    case '\n':
    case '\r':
      advanceForLF(&cur, end);
      col = 0;
      row++;
      break;
    case ' ':
      col++;
      break;
    default:
      // Make sure there's enough room
      if (col >= is_white.size())
        is_white.resize(col + 1, true);
      is_white[col] = false;
    col++;
    }

  }

  return is_white;
}

// [[Rcpp::export]]
List whitespaceColumns(List sourceSpec, int n = 100) {
  SourcePtr source = Source::create(sourceSpec);

  std::vector<bool> empty = emptyCols_(source->begin(), source->end(), n);
  std::vector<int> begin, end;

  bool in_col = false;

  for (size_t i = 0; i < empty.size(); ++i) {
    if (in_col && empty[i]) {
      end.push_back(i);
      in_col = false;
    } else if (!in_col && !empty[i]) {
      begin.push_back(i);
      in_col = true;
    }
  }

  if (in_col)
    end.push_back(empty.size());

  return List::create(
    _["begin"] = begin,
    _["end"] = end
  );
}
