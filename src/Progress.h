#ifndef FASTREAD_PROGRESS_H_
#define FASTREAD_PROGRESS_H_

#include <Rcpp.h>
#include <sstream>
#include <time.h>

inline int now() { return clock() / CLOCKS_PER_SEC; }

inline std::string clearLine(int width = 50) {
  return "\r" + std::string(' ', width) + "\r";
}

inline std::string showTime(int x) {
  if (x < 60) {
    return tfm::format("%i s", x);
  } else if (x < 60 * 60) {
    return tfm::format("%i m", x / 60);
  } else {
    return tfm::format("%i h", x / (60 * 60));
  }
}

class Progress {
  int timeMin_, timeInit_, timeStop_, width_;
  bool show_, stopped_;

public:
  Progress(int min = 5, int width = Rf_GetOptionWidth())
      : timeMin_(min), timeInit_(now()), timeStop_(now()), width_(width),
        show_(false), stopped_(false) {}

  void stop() {
    timeStop_ = now();
    stopped_ = true;
  }

  void show(std::pair<double, size_t> progress) {
    double prop = progress.first, size = progress.second / (1024 * 1024);

    double est = (now() - timeInit_) / prop;
    if (!show_) {
      if (est > timeMin_) {
        show_ = true;
      } else {
        return;
      }
    }

    std::stringstream labelStream;
    tfm::format(labelStream, " %3d%%", (int)(prop * 100));
    if (size > 0) {
      tfm::format(labelStream, " %4.0f MB", size);
    }

    std::string label = labelStream.str();

    int barSize = width_ - label.size() - 2;
    if (barSize < 0) {
      return;
    }
    int nbars = prop * barSize;
    int nspaces = (1 - prop) * barSize;
    std::string bars(nbars, '='), spaces(nspaces, ' ');
    Rcpp::Rcout << '\r' << '|' << bars << spaces << '|' << label;
  }

  ~Progress() {
    try {
      if (!show_)
        return;

      if (!stopped_)
        timeStop_ = now();
      Rcpp::Rcout << "\n";

    } catch (...) {
    }
  }
};

#endif
