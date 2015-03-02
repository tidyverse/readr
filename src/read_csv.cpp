#include <Rcpp.h>
#include "fastread.h"
using namespace Rcpp;
using namespace fastread;

template <typename Source>
int source_count_lines(Source& source) {
  if (!source.can_seek()) stop("cannot seek");

  double pos = source.byte_offset();
  int n = source.count_lines();
  source.seek(pos);

  return n;
}

template<typename Source>
List read_csv(Source source, List parser_spec, CharacterVector col_names,
              int n = 0, int skip = 0) {

  if (n <= 0)
    n = source_count_lines(source) - skip;
  for (int i = 0; i < skip; ++i)
    source.skip_line();

  // Create a vector input parser for each column, figuring out how many
  // columns that the output will have.
  int src_cols = col_names.size();
  int dst_cols = 0;

  std::vector<VectorInput<Source>*> parsers;
  for(int i = 0; i < src_cols; ++i){
    parsers.push_back(create_parser<Source>(parser_spec[i], n, source));
    if (!parsers[i]->skip()) dst_cols++;
  }

  // Load data into vector parsers
  for (int i = 0; i < n; ++i) {
    if (i % 4096 == 0) Rcpp::checkUserInterrupt();
    for (int j = 0; j < src_cols; j++) {
      parsers[j]->set(i);
    }
  }

  // Create output data frame
  List out(dst_cols);
  CharacterVector dst_names(dst_cols);

  int k = 0;
  for(int i = 0; i < src_cols; i++){
    if (parsers[i]->skip()) continue;
    out[k] = parsers[i]->get();
    dst_names[k] = col_names[i];
    k++;
  }
  out.attr("class") = CharacterVector::create("tbl_df", "data.frame");
  out.attr("names") = dst_names;
  out.attr("row.names") = IntegerVector::create(NA_INTEGER, -n);

  // Clean up parsers
  for(int i = 0; i < parsers.size(); i++) {
    delete parsers[i];
  }

  return out;
}

// [[Rcpp::export]]
List read_csv_from_file(std::string path, List parser_spec,
                        CharacterVector col_names, int n = 0, int skip = 0) {

  MMapSource<> source(path);
  return read_csv(source, parser_spec, col_names, n, skip);
}

// [[Rcpp::export]]
List read_csv_from_connection(SEXP conn, List parser_spec,
                              CharacterVector col_names, int n = 0, int skip = 0) {

  ReadConnectionSource<> source(conn);
  return read_csv(source, parser_spec, col_names, n, skip);
}
