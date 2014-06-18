#include <Rcpp.h>
#include <istream>
using namespace Rcpp;

// [[Rcpp::export]]
std::vector<std::string> parse_line_delimited(
                                        std::string x,
                                        std::string delim_ = ",",
                                        std::string quote_ = "\"",
                                        bool collapse = false,
                                        bool backslash_escape = false,
                                        bool double_escape = false,
                                        bool strict = false) {
  char delim = delim_[0];
  char quote = quote_[0];

  std::string field = "";
  std::vector<std::string> out;
  bool in_string = false;

  std::istringstream stream(x);
  char c;
  while ((c = stream.get()) && stream.good()) {
    if (!in_string && c == delim) {
      if (collapse) {
        while(stream.peek() == delim)
          stream.get();
      }
      out.push_back(field);
      field = "";
    } else if (c == quote) {
      if (double_escape && stream.peek() == quote) {
        stream.get();
        field.push_back(quote);
      } else {
        in_string = !in_string;
      }
    } else if (backslash_escape && c == '\\') {
      if (strict && stream.peek() == EOF) {
        stop("Unterminated escape");
      }
      field.push_back(stream.get());
    } else {
      field.push_back(c);
    }
  }
  if (strict && in_string) {
    stop("Unterminated string");
  }

  if (field != "")
    out.push_back(field);


  return out;
}
