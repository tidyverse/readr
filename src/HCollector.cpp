#include <Rcpp.h>
using namespace Rcpp;

#include "HCollector.h"
#include "HCollectorLogical.h"
#include "HCollectorInteger.h"
#include "HCollectorDouble.h"
#include "HCollectorCharacter.h"

boost::shared_ptr<Collector> collectorCreate(List spec) {
  String type = (as<CharacterVector>(spec["type"]))[0];

  if (type == "logical"  )
    return boost::shared_ptr<Collector>(new CollectorLogical());
  if (type == "integer"  )
    return boost::shared_ptr<Collector>(new CollectorInteger());
  if (type == "double"   )
    return boost::shared_ptr<Collector>(new CollectorDouble());
  if (type == "character")
    return boost::shared_ptr<Collector>(new CollectorCharacter());

  Rcpp::stop("Unsupported column type");
  return boost::shared_ptr<Collector>();
}
