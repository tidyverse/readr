#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "SourceFile.h"
#include "SourceString.h"
#include "SourceRaw.h"

SourcePtr Source::create(List spec) {
  std::string subclass(as<CharacterVector>(spec.attr("class"))[0]);

  int skip = as<int>(spec["skip"]);

  if (subclass == "source_raw") {
    return SourcePtr(new SourceRaw(as<RawVector>(spec[0]), skip));
  } else if (subclass == "source_string") {
    return SourcePtr(new SourceString(as<CharacterVector>(spec[0]), skip));
  } else if (subclass == "source_file") {
    std::string path(as<CharacterVector>(spec[0])[0]);
    return SourcePtr(new SourceFile(path, skip));
  }

  Rcpp::stop("Unknown source type");
  return SourcePtr();
}
