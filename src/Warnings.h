#ifndef READ_WARNINGS_H_
#define READ_WARNINGS_H_

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

  Rcpp::RObject addAsAttribute(Rcpp::RObject x) {
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

  Rcpp::List asDataFrame() {
    Rcpp::List out = Rcpp::List::create(
        Rcpp::_["row"] = Rcpp::wrap(row_),
        Rcpp::_["col"] = Rcpp::wrap(col_),
        Rcpp::_["expected"] = Rcpp::wrap(expected_),
        Rcpp::_["actual"] = Rcpp::wrap(actual_));
    out.attr("class") =
        Rcpp::CharacterVector::create("tbl_df", "tbl", "data.frame");
    out.attr("row.names") = Rcpp::IntegerVector::create(NA_INTEGER, -size());

    return out;
  }
};

#endif
