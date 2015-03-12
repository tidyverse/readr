#ifndef FASTREAD_WIN_H_
#define FASTREAD_WIN_H_

#ifdef WIN32

#include <time.h>

typedef	long time_t;

time_t timegm(struct tm *tm);
char *strptime(const char *buf, const char *fmt, struct tm *tm);

#endif // WIN32

#endif
