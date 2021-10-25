#ifndef __YMD_H__
#define __YMD_H__

#include "ErrorType.h"

#include <stdint.h>

struct YMD {
    int_least32_t year;
    uint_least8_t month;
    uint_least8_t day;
};

UniversalCalendarErrorCode YMD__toString(struct YMD* const restrict ymd, char** const restrict output, const char* const restrict prefix);

#endif