#include <Rcpp.h>
using namespace Rcpp;
#include "grisu3.h"
#include "write_connection.h"
#include <boost/iostreams/stream.hpp> // stream
#include <fstream>

// Defined later to make copyright clearer
template <class Stream>
void stream_delim(
    Stream& output, const RObject& x, int i, char delim, const std::string& na);

template <class Stream>
void stream_delim_row(
    Stream& output,
    const Rcpp::List& x,
    int i,
    char delim,
    const std::string& na) {
  int p = Rf_length(x);

  for (int j = 0; j < p - 1; ++j) {
    stream_delim(output, x.at(j), i, delim, na);
    output << delim;
  }
  stream_delim(output, x.at(p - 1), i, delim, na);

  output << '\n';
}

bool needs_quote(const char* string, char delim, const std::string& na) {
  if (string == na)
    return true;

  for (const char* cur = string; *cur != '\0'; ++cur) {
    if (*cur == '\n' || *cur == '\r' || *cur == '"' || *cur == delim)
      return true;
  }

  return false;
}

template <class Stream>
void stream_delim(
    Stream& output, const char* string, char delim, const std::string& na) {
  bool quotes = needs_quote(string, delim, na);

  if (quotes)
    output << '"';

  for (const char* cur = string; *cur != '\0'; ++cur) {
    switch (*cur) {
    case '"':
      output << "\"\"";
      break;
    default:
      output << *cur;
    }
  }

  if (quotes)
    output << '"';
}

template <class Stream>
void stream_delim(
    Stream& output,
    const List& df,
    char delim,
    const std::string& na,
    bool col_names = true,
    bool bom = false) {
  int p = Rf_length(df);
  if (p == 0)
    return;

  if (bom) {
    output << "\xEF\xBB\xBF";
  }

  if (col_names) {
    CharacterVector names = as<CharacterVector>(df.attr("names"));
    for (int j = 0; j < p; ++j) {
      stream_delim(output, names, j, delim, na);
      if (j != p - 1)
        output << delim;
    }
    output << '\n';
  }

  RObject first_col = df[0];
  int n = Rf_length(first_col);

  for (int i = 0; i < n; ++i) {
    stream_delim_row(output, df, i, delim, na);
  }
}

// [[Rcpp::export]]
std::string stream_delim_(
    const List& df,
    RObject connection,
    char delim,
    const std::string& na,
    bool col_names = true,
    bool bom = false) {
  if (connection == R_NilValue) {
    std::ostringstream output;
    stream_delim(output, df, delim, na, col_names, bom);
    return output.str();
  } else {
    boost::iostreams::stream<connection_sink> output(connection);
    stream_delim(output, df, delim, na, col_names, bom);
  }

  return "";
}

// =============================================================================
// Derived from EncodeElementS in RPostgreSQL
// Written by: tomoakin@kenroku.kanazawa-u.ac.jp
// License: GPL-2

template <class Stream>
void stream_delim(
    Stream& output,
    const RObject& x,
    int i,
    char delim,
    const std::string& na) {
  switch (TYPEOF(x)) {
  case LGLSXP: {
    int value = LOGICAL(x)[i];
    if (value == TRUE) {
      output << "TRUE";
    } else if (value == FALSE) {
      output << "FALSE";
    } else {
      output << na;
    }
    break;
  }
  case INTSXP: {
    int value = INTEGER(x)[i];
    if (value == NA_INTEGER) {
      output << na;
    } else {
      output << value;
    }
    break;
  }
  case REALSXP: {
    double value = REAL(x)[i];
    if (!R_FINITE(value)) {
      if (ISNA(value)) {
        output << na;
      } else if (ISNAN(value)) {
        output << "NaN";
      } else if (value > 0) {
        output << "Inf";
      } else {
        output << "-Inf";
      }
    } else {
      char str[32];
      int len = dtoa_grisu3(value, str);
      output.write(str, len);
    }
    break;
  }
  case STRSXP: {
    if (STRING_ELT(x, i) == NA_STRING) {
      output << na;
    } else {
      stream_delim(output, Rf_translateCharUTF8(STRING_ELT(x, i)), delim, na);
    }
    break;
  }
  default:
    Rcpp::stop(
        "Don't know how to handle vector of type %s.", Rf_type2char(TYPEOF(x)));
  }
}
