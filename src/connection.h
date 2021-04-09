#pragma once

#include "cpp11/function.hpp"
#include "cpp11/raws.hpp"

inline SEXP R_GetConnection(SEXP con) { return con; }

inline size_t R_ReadConnection(SEXP con, void* buf, size_t n) {
  static auto readBin = cpp11::package("base")["readBin"];

  cpp11::raws res(
      readBin(con, cpp11::writable::raws(static_cast<R_xlen_t>(0)), n));
  memcpy(buf, RAW(res), res.size());

  return res.size();
}

inline size_t R_WriteConnection(SEXP con, void* buf, size_t n) {
  static auto writeBin = cpp11::package("base")["writeBin"];

  cpp11::writable::raws payload(n);
  memcpy(RAW(payload), buf, n);

  writeBin(payload, con);

  return n;
}

inline void write_bytes(SEXP con, const char* bytes, size_t size) {
  size_t write_size;
  if ((write_size = R_WriteConnection(con, (void*)bytes, size)) != size) {
    cpp11::stop("write failed, expected %l, got %l", size, write_size);
  }
}
