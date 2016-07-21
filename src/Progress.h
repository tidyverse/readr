#pragma once

#include <time.h>

inline int now() {
  return clock() / CLOCKS_PER_SEC;
}

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

  Progress(int min = 5, int width = 80):
    timeMin_(min),
    timeInit_(now()),
    timeStop_(now()),
    width_(width),
    show_(false),
    stopped_(false)
  {
  }

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

    // double time_left = (1 - prop) * est;
    int nbars = prop * width_, nspaces = (1 - prop) * width_;

    std::string bars(nbars, '='), spaces(nspaces, ' ');
    tfm::format(Rcpp::Rcout, "\r|%s%s| %3d%%", bars, spaces, (int) (prop * 100));
    if (size > 0) {
      tfm::format(Rcpp::Rcout, " %4.0f MB", size);
    } else {
      tfm::format(Rcpp::Rcout, "           ");
    }
  }

  ~Progress() {
    try {
      if (!show_)
        return;

      if (!stopped_)
        timeStop_ = now();
      Rcpp::Rcout << "\n";

    } catch (...) {}
  }

};

