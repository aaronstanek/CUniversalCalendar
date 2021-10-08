#ifndef __YMD_H__
#define __YMD_H__

#include <stdint.h>

struct YMD {
    int_least32_t year;
    uint_least8_t month;
    uint_least8_t day;
};

#endif