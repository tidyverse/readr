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
      cpp11::strings colNames = cpp11::strings());

  Reader(
      SourcePtr source,
      TokenizerPtr tokenizer,
      CollectorPtr collector,
      bool progress,
      cpp11::strings colNames = cpp11::strings());

  cpp11::sexp readToDataFrame(int lines = -1);
  cpp11::sexp meltToDataFrame(cpp11::list locale_, int lines = -1);

  template <typename T> T readToVector(int lines) {
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

  const static int progressStep_ = 10000;

  void init(cpp11::strings colNames);
  int read(int lines = -1);
  int melt(cpp11::list locale_, int lines = -1);
  void checkColumns(int i, int j, int n);

  void collectorsResize(int n);
  void collectorsClear();
};
