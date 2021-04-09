#include "cpp11/list.hpp"
#include "cpp11/sexp.hpp"
#include "cpp11/strings.hpp"

#include "connection.h"
#include <fstream>
#include <ostream>

[[cpp11::register]] void write_lines_(
    cpp11::strings lines,
    cpp11::sexp connection,
    const std::string& na,
    const std::string& sep) {

  for (cpp11::strings::const_iterator i = lines.begin(); i != lines.end();
       ++i) {
    if (*i == NA_STRING) {
      write_bytes(connection, na.c_str(), na.size());
    } else {
      const char* str = Rf_translateCharUTF8(*i);
      write_bytes(connection, str, strlen(str));
    }
    write_bytes(connection, sep.c_str(), sep.size());
  }

  return;
}

[[cpp11::register]] void write_lines_raw_(
    cpp11::list x, cpp11::sexp connection, const std::string& sep) {

  for (int i = 0; i < x.size(); ++i) {
    cpp11::raws y(x.at(i));
    write_bytes(
        connection,
        reinterpret_cast<const char*>(RAW(y)),
        y.size() * sizeof(RAW(y)[0]));
    write_bytes(connection, sep.c_str(), sep.size());
  }

  return;
}

[[cpp11::register]] void write_file_(std::string x, cpp11::sexp connection) {
  write_bytes(connection, x.c_str(), x.size());
  return;
}

[[cpp11::register]] void
write_file_raw_(cpp11::raws x, cpp11::sexp connection) {

  write_bytes(
      connection,
      reinterpret_cast<const char*>(RAW(x)),
      x.size() * sizeof(RAW(x)[0]));
  return;
}
