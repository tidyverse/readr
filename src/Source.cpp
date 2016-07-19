#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "SourceFile.h"
#include "SourceString.h"
#include "SourceRaw.h"

SourcePtr Source::create(List spec) {
  return SourcePtr(Source::createDumbPtr(spec));
}

Source* Source::createDumbPtr(List spec) {
  std::string subclass(as<CharacterVector>(spec.attr("class"))[0]);

  int skip = as<int>(spec["skip"]);
  std::string comment = as<std::string>(spec["comment"]);

  if (subclass == "source_raw") {
    return new SourceRaw(as<RawVector>(spec[0]), skip, comment);
  } else if (subclass == "source_string") {
    return new SourceString(as<CharacterVector>(spec[0]), skip, comment);
  } else if (subclass == "source_file") {
    std::string path(as<CharacterVector>(spec[0])[0]);
    return new SourceFile(path, skip, comment);
  }

  Rcpp::stop("Unknown source type");
  return NULL;
}
