#include "write_connection.h"
#include <boost/iostreams/stream.hpp> // stream
#include <fstream>
#include <ostream>

#include "cpp11/list.hpp"

#include <Rcpp.h>
using namespace Rcpp;

[[cpp11::export]] void write_lines_(
    const CharacterVector& lines,
    RObject connection,
    const std::string& na,
    const std::string& sep) {
  boost::iostreams::stream<connection_sink> output(connection);
  for (CharacterVector::const_iterator i = lines.begin(); i != lines.end();
       ++i) {

    if (CharacterVector::is_na(*i)) {
      output << na << sep;
    } else {
      output << Rf_translateCharUTF8(*i) << sep;
    }
  }

  return;
}

[[cpp11::export]] void
write_lines_raw_(cpp11::list x, RObject connection, const std::string& sep) {

  boost::iostreams::stream<connection_sink> output(connection);

  for (int i = 0; i < x.size(); ++i) {
    RawVector y = x.at(i);
    output.write(reinterpret_cast<const char*>(&y[0]), y.size() * sizeof(y[0]));
    output << sep;
  }

  return;
}

[[cpp11::export]] void write_file_(std::string x, RObject connection) {
  boost::iostreams::stream<connection_sink> out(connection);

  out << x;
  return;
}

[[cpp11::export]] void write_file_raw_(RawVector x, RObject connection) {

  boost::iostreams::stream<connection_sink> output(connection);

  output.write(reinterpret_cast<const char*>(&x[0]), x.size() * sizeof(x[0]));
  return;
}
