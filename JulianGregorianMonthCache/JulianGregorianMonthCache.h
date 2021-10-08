#ifndef __JULIANGREGORIANMONTHCACHE_H__
#define __JULIANGREGORIANMONTHCACHE_H__

#include <stdint.h>

struct JulianGregorianMonthCache {
    uint_least8_t length[12];
    uint_least8_t lengthLeap[12];
    uint_least16_t total[12];
    uint_least16_t totalLeap[12];
};

void JulianGregorianMonthCache__constructor(struct JulianGregorianMonthCache* const restrict cache);

#endif