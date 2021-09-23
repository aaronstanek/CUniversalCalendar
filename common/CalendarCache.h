#ifndef __CALENDARCACHE_H__
#define __CALENDARCACHE_H__

#include "../dayOfWeek/DOWcache.h"
#include "../JulianGregorianMonthCache/JulianGregorianMonthCache.h"

struct CalendarCache {
    struct DOWcache dow;
    struct JulianGregorianMonthCache jgMonth;
};

void CalendarCache__constructor(struct CalendarCache* const restrict cache);

#endif