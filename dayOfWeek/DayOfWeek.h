#ifndef __DAYOFWEEK_H__
#define __DAYOFWEEK_H__

#include "../common/CalendarCache.h"

const char* dayOfWeekString(const struct CalendarCache* const restrict cache, const long udn);

int dayOfWeekISO(const long udn);

#endif