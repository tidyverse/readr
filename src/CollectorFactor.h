#ifndef FASTREAD_COLLECTORFACTOR_H_
#define FASTREAD_COLLECTORFACTOR_H_

#include <Rcpp.h>
#include "Collector.h"

class CollectorFactor : public Collector {
  Rcpp::CharacterVector levels_;
  std::map<std::string,int> levelset_;
  bool ordered_;

public:
  CollectorFactor(Rcpp::CharacterVector levels, bool ordered):
    Collector(Rcpp::IntegerVector()), levels_(levels), ordered_(ordered)
  {
    int n = levels.size();

    for (int i = 0; i < n; ++i) {
      const char* level = Rf_translateCharUTF8(STRING_ELT(levels, i));
      std::string std_level(level);
      levelset_.insert(std::make_pair(std_level, i));
    }
  }

  void setValue(int i, const Token& t) {
    INTEGER(column_)[i] = parse(t);
  }

  int parse(const Token& t) {
    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      SourceIterators string = t.getString(&buffer);

      std::string std_string(string.first, string.second);
      std::map<std::string,int>::iterator it = levelset_.find(std_string);
      if (it == levelset_.end()) {
        warn(t.row(), t.col(), "value in level set", std_string);
        return NA_INTEGER;
      } else {
        return it->second + 1;
      }
    };
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      return NA_INTEGER;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }
    return NA_INTEGER;
  }

  Rcpp::RObject vector() {
    if (ordered_) {
      column_.attr("class") = Rcpp::CharacterVector::create("ordered", "factor");
    } else {
      column_.attr("class") = "factor";
    }

    column_.attr("levels") = levels_;
    return column_;
  };


};

#endif
