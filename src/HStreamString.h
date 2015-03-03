#ifndef FASTREAD_HSTREAMSTRING_H
#define FASTREAD_HSTREAMSTRING_H

#include <Rcpp.h>

typedef const char* StreamIterator;

class StreamString {
  Rcpp::RObject string_;
  int row_, col_;

  StreamIterator begin_, end_, cur_;

public:

  StreamString(Rcpp::CharacterVector x) : row_(0), col_(0) {
    string_ = x[0];

    begin_ = CHAR(string_);
    end_ = begin_ + Rf_length(string_);
    cur_ = begin_;
  }

  StreamIterator pos() {
    return cur_;
  }

  char get() {
    if (cur_ >= end_)
      return EOF;

    return *cur_++;
  }

  char peek() {
    if (cur_ >= end_)
      return EOF;

    return *cur_;
  }

  void nextRow() {
    row_++;
    col_ = 0;
  }
  void nextCol() {
    col_++;
  }
  int col() {
    return col_;
  }
  int row() {
    return row_;
  }

};

#endif
