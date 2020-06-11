#include "cpp11/list.hpp"
#include "cpp11/sexp.hpp"
#include "cpp11/strings.hpp"

#include "write_connection.h"
#include <boost/iostreams/stream.hpp> // stream
#include <fstream>
#include <ostream>

[[cpp11::export]] void write_lines_(
    cpp11::strings lines,
    cpp11::sexp connection,
    const std::string& na,
    const std::string& sep) {
  boost::iostreams::stream<connection_sink> output(connection);
  for (cpp11::strings::const_iterator i = lines.begin(); i != lines.end();
       ++i) {

    if (*i == NA_STRING) {
      output << na << sep;
    } else {
      output << Rf_translateCharUTF8(*i) << sep;
    }
  }

  return;
}

[[cpp11::export]] void write_lines_raw_(
    cpp11::list x, cpp11::sexp connection, const std::string& sep) {

  boost::iostreams::stream<connection_sink> output(connection);

  for (int i = 0; i < x.size(); ++i) {
    cpp11::raws y(x.at(i));
    output.write(
        reinterpret_cast<const char*>(RAW(y)), y.size() * sizeof(RAW(y)[0]));
    output << sep;
  }

  return;
}

[[cpp11::export]] void write_file_(std::string x, cpp11::sexp connection) {
  boost::iostreams::stream<connection_sink> out(connection);

  out << x;
  return;
}

[[cpp11::export]] void write_file_raw_(cpp11::raws x, cpp11::sexp connection) {

  boost::iostreams::stream<connection_sink> output(connection);

  output.write(
      reinterpret_cast<const char*>(RAW(x)), x.size() * sizeof(RAW(x)[0]));
  return;
}
