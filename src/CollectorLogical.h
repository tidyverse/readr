#ifndef FASTREAD_COLLECTORLOGICAL_H_
#define FASTREAD_COLLECTORLOGICAL_H_

#include <Rcpp.h>
#include <cstring>
#include "Collector.h"

class CollectorLogical : public Collector {
public:
  CollectorLogical(): Collector(Rcpp::LogicalVector()) {
  }

  void setValue(int i, const Token& t) {
    LOGICAL(column_)[i] = parse(t);
  }

  int parse(const Token& t) {

    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      SourceIterators string = t.getString(&buffer);
      int size = string.second - string.first;

      if (size == 1) {
        if (*string.first == 'T') return 1;
        if (*string.first == 'F') return 0;
      } else if (size == 4) {
        if (strncmp(string.first, "TRUE", 4) == 0) return 1;
      } else if (size == 5) {
        if (strncmp(string.first, "FALSE", 5) == 0) return 0;
      }
      return warn(t, string);
    };
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      return NA_LOGICAL;
      break;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }

    return false;
  }

  static bool canParse(const std::string& x) {
    return x == "T" || x == "F" || x == "TRUE" || x == "FALSE";
  }

private:

  int warn(const Token& t, SourceIterators string) {
    Rcpp::warning("At [%i, %i]: expected T/F/TRUE/FALSE, got '%s'",
      t.row() + 1, t.col() + 1, std::string(string.first, string.second));
    return NA_LOGICAL;
  }

};

#endif
