#include <Rcpp.h>
#include <istream>
#include <fstream>
using namespace Rcpp;

template<typename Stream>
std::map<char,int> count_char(Stream& stream, int n = 30, int skip = 0,
                              std::string comment_ = "",
                              std::string quote_ = "\"",
                              bool backslash_escape = false,
                              bool double_escape = false,
                              bool include_alpha = false,
                              bool include_num = false,
                              bool include_whitespace = false) {
  char quote = quote_[0];
  char comment = comment_[0];

  for(int i = 0; i < skip; ++i) {
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  std::string field = "";
  std::map<char,int> dict;
  bool in_string = false;
  int lines = 0;

  char c;
  while ((c = stream.get()) && stream.good()) {
    if (c == quote && !(double_escape && stream.peek() == quote)) {
      in_string = !in_string;
    } else if (backslash_escape && c == '\\') {
      if (stream.peek() != EOF) {
        dict[c]++;
        c = stream.get();
        dict[c]++;
      }
    } else if (!in_string) {
      if (c == comment) {
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }
      if (!include_alpha && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
        continue;
      }
      if (!include_num && c >= '0' && c <= '9') {
        continue;
      }
      if (!include_whitespace && (c == ' ' || c == '\t' || c == '\r')) {
        continue;
      }
      dict[c]++;

      if (c == '\n') lines++;
      if (lines >= n) break;
    }
  }

  return dict;
}


// [[Rcpp::export]]
std::map<char,int> count_char_from_file(std::string x, int n = 30, int skip = 0,
                                        std::string comment_ = "",
                                        std::string quote_ = "\"",
                                        bool backslash_escape = false,
                                        bool double_escape = false,
                                        bool include_alpha = false,
                                        bool include_num = false) {

  std::fstream stream(x.c_str());
  return count_char(stream, n, skip, comment_, quote_, backslash_escape,
                    double_escape, include_alpha, include_num);
}

// [[Rcpp::export]]
std::map<char,int> count_char_from_string(std::string x, int n = 30, int skip = 0,
                                          std::string comment_ = "",
                                          std::string quote_ = "\"",
                                          bool backslash_escape = false,
                                          bool double_escape = false,
                                          bool include_alpha = false,
                                          bool include_num = false) {

  std::istringstream stream(x);
  return count_char(stream, n, skip, comment_, quote_, backslash_escape,
                    double_escape, include_alpha, include_num);
}
