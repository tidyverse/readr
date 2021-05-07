#include "cpp11/list.hpp"
#include "cpp11/sexp.hpp"
#include "cpp11/strings.hpp"

#include "connection.h"
#include "grisu3.h"
#include <fstream>
#include <sstream>

enum quote_escape_t { DOUBLE = 1, BACKSLASH = 2, NONE = 3 };

void stream_delim(
    const cpp11::sexp& connection,
    const cpp11::sexp& x,
    int i,
    char delim,
    const std::string& na,
    quote_escape_t escape);

void stream_delim_row(
    const cpp11::sexp& connection,
    const cpp11::list& x,
    int i,
    char delim,
    const std::string& na,
    quote_escape_t escape,
    const char* eol) {
  int p = Rf_length(x);

  for (int j = 0; j < p - 1; ++j) {
    stream_delim(connection, x.at(j), i, delim, na, escape);
    write_bytes(connection, &delim, 1);
  }
  stream_delim(connection, x.at(p - 1), i, delim, na, escape);

  write_bytes(connection, eol, strlen(eol));
}

bool needs_quote(const char* string, char delim, const std::string& na) {
  if (string == na) {
    return true;

}

  for (const char* cur = string; *cur != '\0'; ++cur) {
    if (*cur == '\n' || *cur == '\r' || *cur == '"' || *cur == delim) {
      return true;

}
  }

  return false;
}

void stream_delim(
    const cpp11::sexp& connection,
    const char* string,
    char delim,
    const std::string& na,
    quote_escape_t escape) {
  bool quotes = needs_quote(string, delim, na);

  if (quotes) {
    write_bytes(connection, "\"", 1);
  }

  for (const char* cur = string; *cur != '\0'; ++cur) {
    switch (*cur) {
    case '"':
      switch (escape) {
      case DOUBLE:
        write_bytes(connection, "\"\"", 2);
        break;
      case BACKSLASH:
        write_bytes(connection, "\\\"", 2);
        break;
      case NONE:
        write_bytes(connection, "\"", 1);
        break;
      }
      break;
    default:
      write_bytes(connection, cur, 1);
    }
  }

  if (quotes) {
    write_bytes(connection, "\"", 1);
  }
}

void validate_col_type(SEXP x, const std::string& name) {
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

void stream_delim(
    const cpp11::sexp& connection,
    const cpp11::list& df,
    char delim,
    const std::string& na,
    bool col_names,
    bool bom,
    quote_escape_t escape,
    const char* eol) {
  int p = Rf_length(df);
  if (p == 0) {
    return;

}

  if (bom) {
    write_bytes(connection, "\xEF\xBB\xBF", 3);
  }

  cpp11::strings names(df.attr("names"));
  // Validate column types
  for (int j = 0; j < p; ++j) {
    validate_col_type(df.at(j), names[j]);
  }

  if (col_names) {
    cpp11::strings names(df.attr("names"));
    for (int j = 0; j < p; ++j) {
      stream_delim(connection, names, j, delim, na, escape);
      if (j != p - 1) {
        write_bytes(connection, &delim, 1);
      }
    }
    write_bytes(connection, eol, strlen(eol));
  }

  cpp11::sexp first_col = df[0];
  int n = Rf_length(first_col);

  for (int i = 0; i < n; ++i) {
    stream_delim_row(connection, df, i, delim, na, escape, eol);
  }
}

[[cpp11::register]] void stream_delim_(
    const cpp11::list& df,
    const cpp11::sexp& connection,
    char delim,
    const std::string& na,
    bool col_names,
    bool bom,
    int quote_escape,
    const char* eol) {
  stream_delim(
      connection,
      df,
      delim,
      na,
      col_names,
      bom,
      static_cast<quote_escape_t>(quote_escape),
      eol);
}

// =============================================================================
// Derived from EncodeElementS in RPostgreSQL
// Written by: tomoakin@kenroku.kanazawa-u.ac.jp
// License: GPL-2

void stream_delim(
    const cpp11::sexp& connection,
    const cpp11::sexp& x,
    int i,
    char delim,
    const std::string& na,
    quote_escape_t escape) {
  switch (TYPEOF(x)) {
  case LGLSXP: {
    int value = LOGICAL(x)[i];
    if (value == TRUE) {
      write_bytes(connection, "TRUE", 4);
    } else if (value == FALSE) {
      write_bytes(connection, "FALSE", 5);
    } else {
      write_bytes(connection, na.c_str(), na.size());
    }
    break;
  }
  case INTSXP: {
    int value = INTEGER(x)[i];
    if (value == NA_INTEGER) {
      write_bytes(connection, na.c_str(), na.size());
    } else {
      char str[32];
      int len = snprintf(str, 32, "%i", value);
      if (len > 32) {
        cpp11::stop("integer too big");
      }
      write_bytes(connection, str, len);
    }
    break;
  }
  case REALSXP: {
    double value = REAL(x)[i];
    if (!R_FINITE(value)) {
      if (ISNA(value) || ISNAN(value)) {
        write_bytes(connection, na.c_str(), na.size());
      } else if (value > 0) {
        write_bytes(connection, "Inf", 3);
      } else {
        write_bytes(connection, "-Inf", 4);
      }
    } else {
      char str[32];
      int len = dtoa_grisu3(value, str);
      write_bytes(connection, str, len);
    }
    break;
  }
  case STRSXP: {
    if (STRING_ELT(x, i) == NA_STRING) {
      write_bytes(connection, na.c_str(), na.size());
    } else {
      stream_delim(
          connection,
          Rf_translateCharUTF8(STRING_ELT(x, i)),
          delim,
          na,
          escape);
    }
    break;
  }
  default:
    cpp11::stop(
        "Don't know how to handle vector of type %s.", Rf_type2char(TYPEOF(x)));
  }
}
