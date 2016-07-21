#include <Rcpp.h>
#include "Collector.h"
#include "Source.h"
#include "Progress.h"

using namespace Rcpp;

class Reader {
  public:
    Reader(SourcePtr source, TokenizerPtr tokenizer, std::vector<CollectorPtr> collectors,
        CharacterVector colNames, LocaleInfo* locale, int progress = 10000);

    RObject readToDataFrame(int lines = -1);

    template <typename T>
    T readToVector(int lines) {
      read(lines);

      return as<T>(collectors_[0]->vector());
    }

  private:
    Warnings warnings_;
    LocaleInfo* locale_;
    TokenizerPtr tokenizer_;
    SourcePtr source_;
    std::vector<CollectorPtr> collectors_;
    Progress progressBar_;
    bool progress_;
    int progressStep_;
    std::vector<int> keptColumns_;
    CharacterVector outNames_;

    int read(int lines = -1);
    void checkColumns(int i, int j, int n);
};
