#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "SourceFile.h"
#include "SourceRaw.h"
#include "SourceString.h"

SourcePtr Source::create(List spec) {
  std::string subclass(as<CharacterVector>(spec.attr("class"))[0]);

  int skip = as<int>(spec["skip"]);
  std::string comment = as<std::string>(spec["comment"]);

  if (subclass == "source_raw") {
    return SourcePtr(new SourceRaw(as<RawVector>(spec[0]), skip, comment));
  } else if (subclass == "source_string") {
    return SourcePtr(
        new SourceString(as<CharacterVector>(spec[0]), skip, comment));
  } else if (subclass == "source_file") {
    std::string path(as<CharacterVector>(spec[0])[0]);
    return SourcePtr(new SourceFile(path, skip, comment));
  }

  Rcpp::stop("Unknown source type");
  return SourcePtr();
}
