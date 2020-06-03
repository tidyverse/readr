#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Rtm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  long tm_gmtoff;
  const char* tm_zone;
};
typedef struct Rtm stm;

time_t my_mktime(stm* const tmp, const char* name);

#ifdef __cplusplus
}
#endif
