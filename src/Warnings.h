#ifndef READ_WARNINGS_H_
#define READ_WARNINGS_H_

#include "cpp11/data_frame.hpp"
#include "cpp11/sexp.hpp"
#include "cpp11/strings.hpp"
#include <string>
#include <vector>

class Warnings {
  std::vector<int> row_, col_;
  std::vector<std::string> expected_, actual_;

public:
  Warnings() {}

  // row and col should be zero-indexed. addWarning converts into one-indexed
  void addWarning(
      int row,
      int col,
      const std::string& expected,
      const std::string& actual) {
    row_.push_back(row == -1 ? NA_INTEGER : row + 1);
    col_.push_back(col == -1 ? NA_INTEGER : col + 1);
    expected_.push_back(expected);
    actual_.push_back(actual);
  }

  cpp11::sexp addAsAttribute(cpp11::sexp x) {
    if (size() == 0)
      return x;

    x.attr("problems") = asDataFrame();
    return x;
  }

  size_t size() { return row_.size(); }

  void clear() {
    row_.clear();
    col_.clear();
    expected_.clear();
    actual_.clear();
  }

  cpp11::data_frame asDataFrame() {
    using namespace cpp11::literals;

    cpp11::writable::data_frame out(
        {"row"_nm = row_,
         "col"_nm = col_,
         "expected"_nm = expected_,
         "actual"_nm = actual_});
    out.attr("class") = {"tbl_df", "tbl", "data.frame"};

    return static_cast<SEXP>(out);
  }
};

#endif
