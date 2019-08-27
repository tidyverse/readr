#pragma once

#include "Rcpp.h"

inline SEXP R_GetConnection(SEXP con) { return con; }

inline size_t R_ReadConnection(SEXP con, void* buf, size_t n) {
  static Rcpp::Function readBin = Rcpp::Environment::base_env()["readBin"];

  Rcpp::RawVector res = readBin(con, Rcpp::RawVector(0), n);
  memcpy(buf, res.begin(), res.size());

  return res.length();
}

inline size_t R_WriteConnection(SEXP con, void* buf, size_t n) {
  static Rcpp::Function writeBin = Rcpp::Environment::base_env()["writeBin"];

  Rcpp::RawVector payload(n);
  memcpy(payload.begin(), buf, n);

  writeBin(payload, con);

  return n;
}
