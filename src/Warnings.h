class Warnings {
  std::vector<int> row_, col_;
  std::vector<std::string> expected_, actual_;

public:

  Warnings() {
  }

  void addWarning(int row, int col, std::string expected, std::string actual) {
    row_.push_back(row);
    col_.push_back(col);
    expected_.push_back(expected);
    actual_.push_back(actual);
  }

  Rcpp::List asDataFrame() {
    Rcpp::List out = Rcpp::List(4);
    out[0] = Rcpp::wrap(row_);
    out[1] = Rcpp::wrap(col_);
    out[2] = Rcpp::wrap(expected_);
    out[3] = Rcpp::wrap(actual_);

    out.attr("names") = Rcpp::CharacterVector::create("row", "col", "expected", "actual");
    out.attr("class") = Rcpp::CharacterVector::create("tbl_df", "tbl", "data.frame");
    out.attr("row.names") = Rcpp::IntegerVector::create(NA_INTEGER, -row_.size());

    return out;
  }

};
