#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "SourceFile.h"
#include "SourceRaw.h"
#include "SourceString.h"
#include "Iconv.h"



SourcePtr Source::create(List spec) {
  std::string subclass(as<CharacterVector>(spec.attr("class"))[0]);

  int skip = as<int>(spec["skip"]);
  SEXP comment = STRING_ELT(spec["comment"], 0);
  std::string encoding = as<std::string>(spec["encoding"]);
  std::string encoded_comment = Iconv::encode(comment, encoding);

  if (subclass == "source_raw") {
    return SourcePtr(new SourceRaw(as<RawVector>(spec[0]), skip, encoded_comment, encoding));
  } else if (subclass == "source_string") {
    return SourcePtr(
        new SourceString(as<CharacterVector>(spec[0]), skip, encoded_comment, encoding));
  } else if (subclass == "source_file") {
    std::string path(as<CharacterVector>(spec[0])[0]);
    return SourcePtr(new SourceFile(path, skip, encoded_comment, encoding));
  }

  Rcpp::stop("Unknown source type");
  return SourcePtr();
}
