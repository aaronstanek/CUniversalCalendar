#ifndef __DAYOFWEEK_H__
#define __DAYOFWEEK_H__

#include "../common/CalendarCache.h"

const char* dayOfWeekString(const struct CalendarCache* const restrict cache, const int_least32_t udn);

int dayOfWeekISO(const int_least32_t udn);

#endif