#ifndef FASTREAD_WIN_H_
#define FASTREAD_WIN_H_

#ifdef WIN32

#include <time.h>

typedef	long time_t;

#ifdef __cplusplus
extern "C" {
#endif

char* strptime(const char *buf, const char *fmt, struct tm *tm);
time_t timegm(struct tm *tm);

#ifdef __cplusplus
}
#endif

#endif // WIN32

#endif
