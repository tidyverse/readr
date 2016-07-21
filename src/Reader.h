#include <Rcpp.h>
#include "Collector.h"
#include "Source.h"
#include "Progress.h"

using namespace Rcpp;

class Reader {
  public:
    Reader(SourcePtr source, TokenizerPtr tokenizer, std::vector<CollectorPtr> collectors, bool progress = true,
        LocaleInfo* locale = NULL, CharacterVector colNames = CharacterVector());

    Reader(SourcePtr source, TokenizerPtr tokenizer, CollectorPtr collector, bool progress = true,
        LocaleInfo* locale = NULL, CharacterVector colNames = CharacterVector());

    RObject readToDataFrame(int lines = -1);

    template <typename T>
    T readToVector(int lines) {
      read(lines);

      return as<T>(collectors_[0]->vector());
    }

    template<typename T>
      RObject readToVectorWithWarnings(int lines) {
        read(lines);

        warnings_.addAsAttribute(as<T>(collectors_[0]->vector()));
      }

  private:
    Warnings warnings_;
    SourcePtr source_;
    TokenizerPtr tokenizer_;
    std::vector<CollectorPtr> collectors_;
    bool progress_;
    LocaleInfo* locale_;
    Progress progressBar_;
    const static int progressStep_ = 10000;
    std::vector<int> keptColumns_;
    CharacterVector outNames_;

    void init(CharacterVector colNames);
    int read(int lines = -1);
    void checkColumns(int i, int j, int n);

    void collectorsResize(int n);
};
