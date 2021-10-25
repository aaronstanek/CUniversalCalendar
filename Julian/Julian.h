#ifndef __JULIAN_H__
#define __JULIAN_H__

#include "../common/CalendarCache.h"
#include "../common/YMD.h"
#include "../common/ErrorType.h"

UniversalCalendarErrorCode JulianEncode(const struct CalendarCache* const restrict cache, struct YMD* const restrict output, const int_fast32_t udn);

UniversalCalendarErrorCode JulianDecode(const struct CalendarCache* const restrict cache, int_fast32_t* output, const struct YMD* const restrict ymd);

#endif