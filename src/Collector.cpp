#include "Collector.h"

#include <Rcpp.h>
using namespace Rcpp;

#include "CollectorLogical.h"
#include "CollectorInteger.h"
#include "CollectorDouble.h"
#include "CollectorCharacter.h"

boost::shared_ptr<Collector> collectorCreate(List spec) {
  std::string subclass(as<CharacterVector>(spec.attr("class"))[0]);

  if (subclass == "collector_logical"  )
    return boost::shared_ptr<Collector>(new CollectorLogical());
  if (subclass == "collector_integer"  )
    return boost::shared_ptr<Collector>(new CollectorInteger());
  if (subclass == "collector_double"   )
    return boost::shared_ptr<Collector>(new CollectorDouble());
  if (subclass == "collector_character")
    return boost::shared_ptr<Collector>(new CollectorCharacter());

  Rcpp::stop("Unsupported column type");
  return boost::shared_ptr<Collector>();
}
