#include "Collector.h"
#include "Progress.h"
#include "Source.h"

#include "cpp11/list.hpp"
#include "cpp11/strings.hpp"

class Reader {
public:
  Reader(
      SourcePtr source,
      TokenizerPtr tokenizer,
      std::vector<CollectorPtr> collectors,
      bool progress,
      const cpp11::strings& colNames = cpp11::strings());

  Reader(
      SourcePtr source,
      TokenizerPtr tokenizer,
      const CollectorPtr& collector,
      bool progress,
      const cpp11::strings& colNames = cpp11::strings());

  cpp11::sexp readToDataFrame(R_xlen_t lines = -1);
  cpp11::sexp meltToDataFrame(const cpp11::list& locale_, R_xlen_t lines = -1);

  template <typename T> T readToVector(R_xlen_t lines) {
    read(lines);

    SEXP x = collectors_[0]->vector();
    T out(x);
    collectorsClear();
    return out;
  }

private:
  Warnings warnings_;
  SourcePtr source_;
  TokenizerPtr tokenizer_;
  std::vector<CollectorPtr> collectors_;
  bool progress_;
  Progress progressBar_;
  std::vector<int> keptColumns_;
  cpp11::writable::strings outNames_;
  bool begun_;
  Token t_;

  const static R_xlen_t progressStep_ = 10000;

  void init(const cpp11::strings& colNames);
  R_xlen_t read(R_xlen_t lines = -1);
  R_xlen_t melt(const cpp11::list& locale_, R_xlen_t lines = -1);
  void checkColumns(int i, int j, int n);

  void collectorsResize(R_xlen_t n);
  void collectorsClear();
};
