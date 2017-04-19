#include <Rcpp.h>
using namespace Rcpp;
#include "write_connection.h"
#include <boost/iostreams/stream.hpp> // stream
#include <fstream>
#include <ostream>

// [[Rcpp::export]]
void write_lines_(
    const CharacterVector& lines, RObject connection, const std::string& na) {
  boost::iostreams::stream<connection_sink> output(connection);
  for (CharacterVector::const_iterator i = lines.begin(); i != lines.end();
       ++i) {

    if (CharacterVector::is_na(*i)) {
      output << na << '\n';
    } else {
      output << Rf_translateCharUTF8(*i) << '\n';
    }
  }

  return;
}

// [[Rcpp::export]]
void write_lines_raw_(List x, RObject connection) {

  boost::iostreams::stream<connection_sink> output(connection);

  for (int i = 0; i < x.length(); ++i) {
    RawVector y = x.at(i);
    output.write(reinterpret_cast<const char*>(&y[0]), y.size() * sizeof(y[0]));
    output << '\n';
  }

  return;
}

// [[Rcpp::export]]
void write_file_(std::string x, RObject connection) {
  boost::iostreams::stream<connection_sink> out(connection);

  out << x;
  return;
}

// [[Rcpp::export]]
void write_file_raw_(RawVector x, RObject connection) {

  boost::iostreams::stream<connection_sink> output(connection);

  output.write(reinterpret_cast<const char*>(&x[0]), x.size() * sizeof(x[0]));
  return;
}
