#include "Collector.h"

#include <Rcpp.h>
using namespace Rcpp;

#include "CollectorSkip.h"
#include "CollectorLogical.h"
#include "CollectorInteger.h"
#include "CollectorDouble.h"
#include "CollectorEuroDouble.h"
#include "CollectorNumeric.h"
#include "CollectorCharacter.h"
#include "CollectorDateTime.h"
#include "CollectorDate.h"
#include "CollectorFactor.h"

CollectorPtr Collector::create(List spec) {
  std::string subclass(as<CharacterVector>(spec.attr("class"))[0]);

  if (subclass == "collector_skip")
    return boost::shared_ptr<Collector>(new CollectorSkip());
  if (subclass == "collector_logical")
    return boost::shared_ptr<Collector>(new CollectorLogical());
  if (subclass == "collector_integer")
    return boost::shared_ptr<Collector>(new CollectorInteger());
  if (subclass == "collector_double")
    return boost::shared_ptr<Collector>(new CollectorDouble());
  if (subclass == "collector_euro_double")
    return boost::shared_ptr<Collector>(new CollectorEuroDouble());
  if (subclass == "collector_numeric")
    return boost::shared_ptr<Collector>(new CollectorNumeric());
  if (subclass == "collector_character")
    return boost::shared_ptr<Collector>(new CollectorCharacter());
  if (subclass == "collector_date") {
    std::string format = as<std::string>(spec["format"]);
    return boost::shared_ptr<Collector>(new CollectorDate(format));
  }
  if (subclass == "collector_datetime") {
    std::string format = as<std::string>(spec["format"]);
    std::string tz = as<std::string>(spec["tz"]);
    return boost::shared_ptr<Collector>(new CollectorDateTime(format, tz));
  }
  if (subclass == "collector_factor") {
    CharacterVector levels = as<CharacterVector>(spec["levels"]);
    bool ordered = as<bool>(spec["ordered"]);
    return boost::shared_ptr<Collector>(new CollectorFactor(levels, ordered));
  }


  Rcpp::stop("Unsupported column type");
  return boost::shared_ptr<Collector>();
}

std::vector<CollectorPtr> collectorsCreate(ListOf<List> specs, Warnings* pWarning) {
  std::vector<CollectorPtr> collectors;
  for (int j = 0; j < specs.size(); ++j) {
    CollectorPtr col = Collector::create(specs[j]);
    col->setWarnings(pWarning);
    collectors.push_back(col);
  }

  return collectors;
}

void collectorsResize(std::vector<CollectorPtr>& collectors, int n) {
  for (size_t j = 0; j < collectors.size(); ++j) {
    collectors[j]->resize(n);
  }
}

// Guess column types ----------------------------------------------------------

typedef bool (*canParseFun)(const std::string&);

static bool canParse(CharacterVector x, const canParseFun& canParse) {
  for (int i = 0; i < x.size(); ++i) {
    if (x[i] == NA_STRING)
      continue;

    if (x[i].size() == 0)
      continue;

    if (!canParse(std::string(x[i])))
      return false;
  }
  return true;
}


bool allMissing(CharacterVector x) {
  for (int i = 0; i < x.size(); ++i) {
    if (x[i] != NA_STRING && x[i].size() > 0)
      return false;
  }
  return true;
}

// [[Rcpp::export]]
std::string collectorGuess(CharacterVector input) {
  if (allMissing(input))
    return "character";

  // Work from strictest to most flexible
  if (canParse(input, CollectorLogical::canParse))
    return "logical";
  if (canParse(input, CollectorInteger::canParse))
    return "integer";
  if (canParse(input, CollectorDouble::canParse))
    return "double";
  if (canParse(input, CollectorEuroDouble::canParse))
    return "euro_double";
  if (canParse(input, CollectorDate::canParse))
    return "date";
  if (canParse(input, CollectorDateTime::canParse))
    return "datetime";

  // Otherwise can always parse as a character
  return "character";
}
