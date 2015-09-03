#ifndef READR_TZ_MANAGER_H_
#define READR_TZ_MANAGER_H_

#include <stdlib.h>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void inline setenv(const char* name, const char* value, int i) {
  ::SetEnvironmentVariable(name, value);
}

void inline unsetenv(const char* name) {
  ::SetEnvironmentVariable(name, NULL);
}

#endif
class TzManager {
  std::string default_, cur_;

  public:

  TzManager(): default_(currentTz()), cur_(default_) {
  }

  TzManager(std::string tz): default_(currentTz()), cur_(default_) {
    setTz(tz);
  }

  ~TzManager() {
    try {
      // Restore default
      setTz(default_);
    } catch (...) {}
  }

  void setTz(std::string tz) {
    if (cur_ == tz)
      return;

    cur_ = tz;
    if (tz == "") {
      unsetenv("TZ");
    } else {
      setenv("TZ", tz.c_str(), 1);
    }

    tzset();
  }

  static std::string currentTz() {
    const char* tz = getenv("TZ");
    return (tz == NULL) ? "" : std::string(tz);
  }
};

#endif
