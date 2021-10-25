#ifndef __GREGORIAN_H__
#define __GREGORIAN_H__

#include "../common/CalendarCache.h"
#include "../common/YMD.h"
#include "../common/ErrorType.h"

UniversalCalendarErrorCode GregorianEncode(const struct CalendarCache* const restrict cache, struct YMD* const restrict output, const int_fast32_t udn);

UniversalCalendarErrorCode GregorianDecode(const struct CalendarCache* const restrict cache, int_fast32_t* output, const struct YMD* const restrict ymd);

#endif