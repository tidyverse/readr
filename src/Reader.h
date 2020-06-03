#include "Collector.h"
#include "Progress.h"
#include "Source.h"

#include "cpp11/list.hpp"

#include <Rcpp.h>

using namespace Rcpp;

class Reader {
public:
  Reader(
      SourcePtr source,
      TokenizerPtr tokenizer,
      std::vector<CollectorPtr> collectors,
      bool progress = true,
      CharacterVector colNames = CharacterVector());

  Reader(
      SourcePtr source,
      TokenizerPtr tokenizer,
      CollectorPtr collector,
      bool progress = true,
      CharacterVector colNames = CharacterVector());

  RObject readToDataFrame(int lines = -1);
  RObject meltToDataFrame(cpp11::list locale_, int lines = -1);

  template <typename T> T readToVector(int lines) {
    read(lines);

    T out = as<T>(collectors_[0]->vector());
    collectorsClear();
    return out;
  }

  template <typename T> RObject readToVectorWithWarnings(int lines) {
    read(lines);

    return static_cast<SEXP>(warnings_.addAsAttribute(
        static_cast<SEXP>(as<T>(collectors_[0]->vector()))));
  }

private:
  Warnings warnings_;
  SourcePtr source_;
  TokenizerPtr tokenizer_;
  std::vector<CollectorPtr> collectors_;
  bool progress_;
  Progress progressBar_;
  std::vector<int> keptColumns_;
  CharacterVector outNames_;
  bool begun_;
  Token t_;

  const static int progressStep_ = 10000;

  void init(CharacterVector colNames);
  int read(int lines = -1);
  int melt(cpp11::list locale_, int lines = -1);
  void checkColumns(int i, int j, int n);

  void collectorsResize(int n);
  void collectorsClear();
};
