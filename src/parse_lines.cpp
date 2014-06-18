#include <Rcpp.h>
#include <istream>
using namespace Rcpp;

// [[Rcpp::export]]
std::vector<std::string> parse_lines(std::string x,
                                     int skip = 0,
                                     std::string line_delim_ = "\n",
                                     std::string comment_char_ = "") {

  char line_delim = line_delim_[0];
  char comment_char = comment_char_[0];

  std::vector<std::string> out;
  std::istringstream stream(x);

  for (int i = 0; i < skip; i++) {
    stream.ignore(std::numeric_limits<std::streamsize>::max(), line_delim);
  }

  std::string line = "";
  char c;
  while((c = stream.get()) && stream.good()) {
    if (c == line_delim) {
      out.push_back(line);
      line = "";
    } else if (c == comment_char) {
      out.push_back(line);
      line = "";
      stream.ignore(std::numeric_limits<std::streamsize>::max(), line_delim);
    } else {
      line.push_back(c);
    }
  }

  if (line != "") {
    out.push_back(line);
  }

  return out;
}
