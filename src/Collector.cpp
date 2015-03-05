#include "Collector.h"

#include <Rcpp.h>
using namespace Rcpp;

#include "CollectorLogical.h"
#include "CollectorInteger.h"
#include "CollectorDouble.h"
#include "CollectorCharacter.h"

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
