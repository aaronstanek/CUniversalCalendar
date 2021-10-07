#ifndef __JULIAN_H__
#define __JULIAN_H__

#include "../common/CalendarCache.h"
#include "../common/YMD.h"

int JulianEncode(const struct CalendarCache* const restrict cache, struct YMD* const restrict output, const long udn);

int JulianDecode(const struct CalendarCache* const restrict cache, long* output, const struct YMD* const restrict ymd);

#endif