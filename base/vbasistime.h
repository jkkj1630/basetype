#ifndef VBASISTIME_H
#define VBASISTIME_H

#include "vtypes.h"
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

inline vint64 vcurNs()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec*1000000000 + ts.tv_nsec;
}

inline vint64 vcurUs()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000000 + tv.tv_usec;
}

inline vint64 vcurMs()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000000 + tv.tv_usec;
}

#endif // VBASISTIME_H
