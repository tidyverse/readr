#include <Rcpp.h>
using namespace Rcpp;
#include <ostream>
#include <fstream>

// [[Rcpp::export]]
void write_lines_(const CharacterVector &lines, const std::string &path, const std::string& na, bool append = false) {

  std::ofstream output(path.c_str(), append ? std::ofstream::app : std::ofstream::trunc);
  if (output.fail()) {
    stop("Failed to open '%s'.", path);
  }
  for (CharacterVector::const_iterator i = lines.begin(); i != lines.end(); ++i) {

    if (CharacterVector::is_na(*i)) {
      output << na << '\n';
    } else {
      output << Rf_translateCharUTF8(*i) << '\n';
    }
  }

  return;
}
