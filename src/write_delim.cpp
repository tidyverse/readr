#include <fstream>
#include <Rcpp.h>
using namespace Rcpp;

// Defined later to make copyright clearer
template <class Stream>
void stream_delim(Stream& output, Rcpp::RObject x, int i);

template <class Stream>
void stream_delim_row(Stream& output, Rcpp::List x, int i, char delim) {
  int p = Rf_length(x);

  for (int j = 0; j < p; ++j) {
    stream_delim(output, x[j], i);
    if (j != p - 1)
      output << delim;
  }
  output << '\n';
}

bool needs_quote(const char* string, char delim = ',') {
  for (const char* cur = string; *cur != '\0'; ++cur) {
    if (*cur == '\n' || *cur == '\r' || *cur == '"' || *cur == delim)
      return true;
  }

  return false;
}

template <class Stream>
void stream_delim(Stream& output, const char* string) {
  bool quotes = needs_quote(string);

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
void stream_delim(Stream& output, List df, char delim, bool col_names = true, bool append = false) {
  int p = Rf_length(df);
  if (p == 0)
    return;

  if (col_names) {
    CharacterVector names = as<CharacterVector>(df.attr("names"));
    for (int j = 0; j < p; ++j) {
      stream_delim(output, names, j);
      if (j != p - 1)
        output << delim;
    }
    output << '\n';
  }

  RObject first_col = df[0];
  int n = Rf_length(first_col);

  for (int i = 0; i < n; ++i) {
    stream_delim_row(output, df, i, delim);
  }
}

// [[Rcpp::export]]
std::string stream_delim(List df, std::string path, char delim, bool col_names = true, bool append = false) {
  if (path == "") {
    std::ostringstream output;
    output.precision(17);
    stream_delim(output, df, delim, col_names, append);
    return output.str();
  } else {
    std::ofstream output(path.c_str(), append ? std::ofstream::app : std::ofstream::trunc);
    output.precision(17);
    stream_delim(output, df, delim, col_names, append);
    return "";
  }
}

// =============================================================================
// Derived from EncodeElementS in RPostgreSQL
// Written by: tomoakin@kenroku.kanazawa-u.ac.jp
// License: GPL-2

template <class Stream>
void stream_delim(Stream& output, RObject x, int i) {
  switch (TYPEOF(x)) {
  case LGLSXP: {
    int value = LOGICAL(x)[i];
    if (value == TRUE) {
      output << "TRUE";
    } else if (value == FALSE) {
      output << "FALSE";
    } else {
      output << "NA";
    }
    break;
  }
  case INTSXP: {
    int value = INTEGER(x)[i];
    if (value == NA_INTEGER) {
      output << "NA";
    } else {
      output << value;
    }
    break;
  }
  case REALSXP:{
    double value = REAL(x)[i];
    if (!R_FINITE(value)) {
      if (ISNA(value)) {
        output << "NA";
      } else if (ISNAN(value)) {
        output << "NaN";
      } else if (value > 0) {
        output << "Inf";
      } else {
        output << "-Inf";
      }
    } else {
      output << value;
    }
    break;
  }
  case STRSXP: {
    RObject value = STRING_ELT(x, i);
    if (value == NA_STRING) {
      output << "NA";
    } else {
      stream_delim(output, Rf_translateCharUTF8(STRING_ELT(x, i)));
    }
    break;
  }
  default:
    Rcpp::stop("Don't know how to handle vector of type %s.",
      Rf_type2char(TYPEOF(x)));
  }
}
