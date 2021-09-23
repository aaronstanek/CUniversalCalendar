#include "CalendarCache.h"

#include <stdlib.h>

void CalendarCache__constructor(struct CalendarCache* const restrict cache) {
    DOWcache__constructor(&(cache->dow));
    JulianGregorianMonthCache__constructor(&(cache->jgMonth));
}