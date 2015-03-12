#ifndef FASTREAD_COLLECTORBDT_H_
#define FASTREAD_COLLECTORBDT_H_

#include <Rcpp.h>
#include <boost/date_time.hpp>
namespace bpt = boost::posix_time;
#include "Collector.h"

const bpt::ptime epoch(boost::gregorian::date(1970, 1, 1));

std::string formatStandard(std::string format);

class CollectorBDT : public Collector {
  std::string format_;
  std::stringstream dateStream_;
  bpt::time_input_facet dateFacet_;

public:
  CollectorBDT(std::string format):
    Collector(Rcpp::NumericVector()),
    format_(format),
    dateFacet_(1) // construct w/ a_ref == 1 so we manage memory
  {
    dateFacet_.format(format.c_str());
    dateStream_.imbue(std::locale(dateStream_.getloc(), &dateFacet_));
  }

  void setValue(int i, const Token& t) {
    REAL(column_)[i] = parse(t);
  }

  double parse(const Token& t) {
    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      SourceIterators string = t.getString(&buffer);
      std::string std_string(string.first, string.second);

      std::pair<bool,int> parsed = parseDate(std_string);
      if (!parsed.first) {
        Rcpp::warning("At [%i, %i]: expected date like '%s', got '%s'",
          t.row() + 1, t.col() + 1, formatStandard(format_), std_string);
        return NA_REAL;
      } else {
        return parsed.second;
      }

    }
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      return NA_REAL;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }

    return 0;
  }

  Rcpp::RObject vector() {
    column_.attr("class") = CharacterVector::create("POSIXct", "POSIXt");
    column_.attr("tzone") = "UTC";
    return column_;
  };

  std::pair<bool,double> parseDate(const std::string& date) {
    bpt::ptime posixDate(bpt::not_a_date_time);

    dateStream_.str(date);
    dateStream_ >> posixDate;

    bool ok = posixDate != bpt::not_a_date_time;
    double sec = (double) (posixDate - epoch).total_seconds();

    return std::make_pair(ok, sec);
  }
};

#endif
