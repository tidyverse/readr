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

  while(stream.good()) {
    if (stream.peek() == comment_char) {
      stream.ignore(std::numeric_limits<std::streamsize>::max(), line_delim);
    } else {
      std::string line;
      std::getline(stream, line, line_delim);
      out.push_back(line);
    }
  }

  return out;
}
