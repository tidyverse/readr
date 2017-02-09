#include <Rcpp.h>
using namespace Rcpp;
#include <ostream>
#include <fstream>
#include "write_connection.h"
#include <boost/iostreams/stream.hpp> // stream

// [[Rcpp::export]]
void write_lines_(const CharacterVector &lines, const std::string &path, const std::string& na, bool append = false) {

  std::ofstream output(path.c_str(), std::ofstream::binary | (append ? std::ofstream::app : std::ofstream::trunc));
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

// [[Rcpp::export]]
void write_lines_connection_(const CharacterVector &lines, RObject connection, const std::string& na) {
  boost::iostreams::stream<connection_sink> output(connection);
  for (CharacterVector::const_iterator i = lines.begin(); i != lines.end(); ++i) {

    if (CharacterVector::is_na(*i)) {
      output << na << '\n';
    } else {
      output << Rf_translateCharUTF8(*i) << '\n';
    }
  }

  return;
}

// [[Rcpp::export]]
void write_lines_raw_(List x, const std::string &path, bool append = false) {
  std::ofstream output(path.c_str(), std::ofstream::binary | (append ? std::ofstream::app : std::ofstream::trunc));

  if (output.fail()) {
    stop("Failed to open '%s'.", path);
  }

  std::ostream_iterator<char> out = std::ostream_iterator<char>(output);
  for (int i = 0;i < x.length();++i) {
    RawVector y = x.at(i);
    std::copy(y.begin(), y.end(), out);
    *out++ = '\n';
  }

  return;
}

// [[Rcpp::export]]
void write_lines_raw_connection_(List x, RObject connection) {

  boost::iostreams::stream<connection_sink> output(connection);

  std::ostream_iterator<char> out = std::ostream_iterator<char>(output);
  for (int i = 0;i < x.length();++i) {
    RawVector y = x.at(i);
    std::copy(y.begin(), y.end(), out);
    *out++ = '\n';
  }

  return;
}

// [[Rcpp::export]]
void write_file_raw_(RawVector x, const std::string &path, bool append = false) {
  std::ofstream output(path.c_str(), std::ofstream::binary | (append ? std::ofstream::app : std::ofstream::trunc));

  if (output.fail()) {
    stop("Failed to open '%s'.", path);
  }

  std::copy(x.begin(), x.end(), std::ostream_iterator<char>(output));

  return;
}

// [[Rcpp::export]]
void write_file_raw_connection_(RawVector x, RObject connection) {

  boost::iostreams::stream<connection_sink> output(connection);
  std::copy(x.begin(), x.end(), std::ostream_iterator<char>(output));

  return;
}

// [[Rcpp::export]]
void write_file_(std::string x, const std::string &path, bool append = false) {
  std::ofstream output(path.c_str(), std::ofstream::binary | (append ? std::ofstream::app : std::ofstream::trunc));

  if (output.fail()) {
    stop("Failed to open '%s'.", path);
  }

  std::copy(x.begin(), x.end(), std::ostream_iterator<char>(output));

  return;
}

// [[Rcpp::export]]
void write_file_connection_(std::string x, RObject connection) {
  boost::iostreams::stream<connection_sink> out(connection);
  out << x;
  return;
}
