#include <Rcpp.h>
using namespace Rcpp;

#include "SourceString.h"
#include "TokenizerDelimited.h"
#include "Collector.h"


// [[Rcpp::export]]
SEXP parseString(CharacterVector x, List spec, int n = 100) {
  SourceString source(x);
  TokenizerDelimited csv(',');
  csv.tokenize(source.begin(), source.end());

  boost::shared_ptr<Collector> out = collectorCreate(spec);
  out->resize(n);

  int i = 0;
  for (Token t = csv.nextToken(); t.type() != TOKEN_EOF; t = csv.nextToken()) {
    out->setValue(i++, t);
  }
  if (i != n)
    out->resize(i);

  return out->vector();
}

// [[Rcpp::export]]
List dataframeString(CharacterVector x, ListOf<List> specs, int n = 100) {
  SourceString source(x);
  TokenizerDelimited csv(',');
  csv.tokenize(source.begin(), source.end());

  int p = specs.size();

  // Initialise collectors
  std::vector<boost::shared_ptr<Collector> > collectors;
  for (int j = 0; j < p; ++j) {
    collectors.push_back(collectorCreate(specs[j]));
    collectors[j]->resize(n);
  }

  for (Token t = csv.nextToken(); t.type() != TOKEN_EOF; t = csv.nextToken()) {
    if (t.col() >= p)
      stop("In row %i, there are %i columns!", t.row(), t.col());
    if (t.row() == n)
      break;

    collectors[t.col()]->setValue(t.row(), t);
  }

  // Save individual columns into a data frame
  List out(p);
  for (int j = 0; j < p; ++j) {
    out[j] = collectors[j]->vector();
  }
  out.attr("class") = CharacterVector::create("tbl_df", "tbl", "data.frame");
  out.attr("row.names") = IntegerVector::create(NA_INTEGER, -n);

  return out;
}
