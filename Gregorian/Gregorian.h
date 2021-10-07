#ifndef __GREGORIAN_H__
#define __GREGORIAN_H__

#include "../common/CalendarCache.h"
#include "../common/YMD.h"

int GregorianEncode(const struct CalendarCache* const restrict cache, struct YMD* const restrict output, const long udn);

int GregorianDecode(const struct CalendarCache* const restrict cache, long* output, const struct YMD* const restrict ymd);

#endif