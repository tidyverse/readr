#ifndef FASTREAD_PROGRESS_H_
#define FASTREAD_PROGRESS_H_

#include "cpp11/R.hpp"
#include <iomanip>
#include <sstream>
#include <time.h>

inline int now() { return clock() / CLOCKS_PER_SEC; }

inline std::string showTime(int x) {
  std::stringstream ss;
  if (x < 60) {
    ss << x << " s";
    return ss.str();
  } else if (x < 60 * 60) {
    ss << x / 60 << " m";
    return ss.str();
  } else {
    ss << x / (60 * 60) << " h";
    return ss.str();
  }
}

class Progress {
  int timeMin_, timeInit_, timeStop_, width_;
  bool show_, stopped_;

public:
  Progress(int min = 5, int width = Rf_GetOptionWidth())
      : timeMin_(min),
        timeInit_(now()),
        timeStop_(now()),
        width_(width),
        show_(false),
        stopped_(false) {}

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
    labelStream << std::setprecision(2) << std::fixed << " "
                << (int)(prop * 100) << "%";
    if (size > 0) {
      labelStream << " " << std::setprecision(0) << size << " MB";
    }

    std::string label = labelStream.str();

    int barSize = width_ - label.size() - 2;
    if (barSize < 0) {
      return;
    }
    int nbars = prop * barSize;
    int nspaces = (1 - prop) * barSize;
    std::string bars(nbars, '='), spaces(nspaces, ' ');
    Rprintf("\r|%s%s|%s", bars.c_str(), spaces.c_str(), label.c_str());
  }

  ~Progress() {
    try {
      if (!show_)
        return;

      if (!stopped_)
        timeStop_ = now();
      Rprintf("\n");

    } catch (...) {
    }
  }
};

#endif
