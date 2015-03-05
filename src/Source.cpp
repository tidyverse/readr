#include "Source.h"

#include <Rcpp.h>
using namespace Rcpp;

#include "SourceFile.h"
#include "SourceString.h"
#include "SourceRaw.h"

SourcePtr sourceCreate(List spec) {
  CharacterVector klass = as<CharacterVector>(spec.attr("class"));
  std::string subclass(klass[klass.size() - 1]);

  if (subclass == "source_raw") {
    return SourcePtr(new SourceRaw(as<RawVector>(spec[0])));
  } else if (subclass == "source_string") {
    return SourcePtr(new SourceString(as<CharacterVector>(spec[0])));
  } else if (subclass == "source_file") {
    std::string path(as<CharacterVector>(spec[0])[0]);
    return SourcePtr(new SourceFile(path));
  }

  Rcpp::stop("Unknown source type");
  return SourcePtr();
}
