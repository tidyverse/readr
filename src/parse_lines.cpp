#include <Rcpp.h>
#include <istream>
#include <fstream>
using namespace Rcpp;

template<typename Stream>
std::vector<std::string> parse_lines(Stream& stream,
                                     int skip = 0,
                                     int n = 0,
                                     std::string delim_ = "\n",
                                     std::string comment_ = "") {

  char delim = delim_[0];
  char comment = comment_[0];

  std::vector<std::string> out;

  for (int i = 0; i < skip; i++) {
    stream.ignore(std::numeric_limits<std::streamsize>::max(), delim);
  }

  std::string line = "";
  char c;
  while((c = stream.get()) && stream.good()) {
    if (c == delim) {
      out.push_back(line);
      line = "";
    } else if (c == comment) {
      out.push_back(line);
      line = "";
      stream.ignore(std::numeric_limits<std::streamsize>::max(), delim);
    } else {
      line.push_back(c);
    }

    // Quit if we have enough lines
    if (n != 0 && out.size() >= n) break;
  }

  if (line != "") {
    out.push_back(line);
  }

  return out;
}


// [[Rcpp::export]]
std::vector<std::string> parse_lines_from_string(std::string x,
                                                 int skip = 0,
                                                 int n = 0,
                                                 std::string delim_ = "\n",
                                                 std::string comment_ = "") {
  std::istringstream stream(x);
  return parse_lines(stream, skip, n, delim_, comment_);
}

// [[Rcpp::export]]
std::vector<std::string> parse_lines_from_file(std::string x,
                                               int skip = 0,
                                               int n = 0,
                                               std::string delim_ = "\n",
                                               std::string comment_ = "") {
  std::fstream stream(x.c_str());
  return parse_lines(stream, skip, n, delim_, comment_);
}
