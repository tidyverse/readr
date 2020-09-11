#include "cpp11/list.hpp"
#include "cpp11/sexp.hpp"
#include "cpp11/strings.hpp"

#include "grisu3.h"
#include "write_connection.h"
#include <boost/iostreams/stream.hpp> // stream
#include <fstream>
#include <sstream>

enum quote_escape_t { DOUBLE = 1, BACKSLASH = 2, NONE = 3 };

// Defined later to make copyright clearer
template <class Stream>
void stream_delim(
    Stream& output,
    const cpp11::sexp& x,
    int i,
    char delim,
    const std::string& na,
    quote_escape_t escape);

template <class Stream>
void stream_delim_row(
    Stream& output,
    const cpp11::list& x,
    int i,
    char delim,
    const std::string& na,
    quote_escape_t escape,
    const char* eol) {
  int p = Rf_length(x);

  for (int j = 0; j < p - 1; ++j) {
    stream_delim(output, x.at(j), i, delim, na, escape);
    output << delim;
  }
  stream_delim(output, x.at(p - 1), i, delim, na, escape);

  output << eol;
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
    Stream& output,
    const char* string,
    char delim,
    const std::string& na,
    quote_escape_t escape) {
  bool quotes = needs_quote(string, delim, na);

  if (quotes)
    output << '"';

  for (const char* cur = string; *cur != '\0'; ++cur) {
    switch (*cur) {
    case '"':
      switch (escape) {
      case DOUBLE:
        output << "\"\"";
        break;
      case BACKSLASH:
        output << "\\\"";
        break;
      case NONE:
        output << '"';
        break;
      }
      break;
    default:
      output << *cur;
    }
  }

  if (quotes)
    output << '"';
}

void validate_col_type(SEXP x, std::string name) {
  switch (TYPEOF(x)) {
  case LGLSXP:
  case INTSXP:
  case REALSXP:
  case STRSXP:
    break;
  default:
    cpp11::stop(
        "Don't know how to handle vector of type %s in column '%s'.",
        Rf_type2char(TYPEOF(x)),
        name.c_str());
  }
}

template <class Stream>
void stream_delim(
    Stream& output,
    const cpp11::list& df,
    char delim,
    const std::string& na,
    bool col_names,
    bool bom,
    quote_escape_t escape,
    const char* eol) {
  int p = Rf_length(df);
  if (p == 0)
    return;

  if (bom) {
    output << "\xEF\xBB\xBF";
  }

  cpp11::strings names(df.attr("names"));
  // Validate column types
  for (int j = 0; j < p; ++j) {
    validate_col_type(df.at(j), names[j]);
  }

  if (col_names) {
    cpp11::strings names(df.attr("names"));
    for (int j = 0; j < p; ++j) {
      stream_delim(output, names, j, delim, na, escape);
      if (j != p - 1)
        output << delim;
    }
    output << eol;
  }

  cpp11::sexp first_col = df[0];
  int n = Rf_length(first_col);

  for (int i = 0; i < n; ++i) {
    stream_delim_row(output, df, i, delim, na, escape, eol);
  }
}

[[cpp11::register]] std::string stream_delim_(
    const cpp11::list& df,
    cpp11::sexp connection,
    char delim,
    const std::string& na,
    bool col_names,
    bool bom,
    int quote_escape,
    const char* eol) {
  if (connection == R_NilValue) {
    std::ostringstream output;
    stream_delim(
        output,
        df,
        delim,
        na,
        col_names,
        bom,
        static_cast<quote_escape_t>(quote_escape),
        eol);
    return output.str();
  } else {
    boost::iostreams::stream<connection_sink> output(connection);
    stream_delim(
        output,
        df,
        delim,
        na,
        col_names,
        bom,
        static_cast<quote_escape_t>(quote_escape),
        eol);
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
    const cpp11::sexp& x,
    int i,
    char delim,
    const std::string& na,
    quote_escape_t escape) {
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
      if (ISNA(value) || ISNAN(value)) {
        output << na;
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
      stream_delim(
          output, Rf_translateCharUTF8(STRING_ELT(x, i)), delim, na, escape);
    }
    break;
  }
  default:
    cpp11::stop(
        "Don't know how to handle vector of type %s.", Rf_type2char(TYPEOF(x)));
  }
}
