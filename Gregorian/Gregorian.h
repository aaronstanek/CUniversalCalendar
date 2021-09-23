#ifndef __GREGORIAN_H__
#define __GREGORIAN_H__

#include "../common/CalendarCache.h"
#include "../common/YMD.h"

int GregorianLeapYear(long year);

int GregorianEncode(const struct CalendarCache* const restrict cache, struct YMD* const restrict output, const long udn);

int GregorianDecode(const struct CalendarCache* const restrict cache, long* output, const struct YMD* const restrict ymd);

int GregorianShift(const struct CalendarCache* const restrict cache, struct YMD* const output, const struct YMD* const ymd, const long shiftValue);

#endif