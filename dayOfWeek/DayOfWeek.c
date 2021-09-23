#include "DayOfWeek.h"

#include "../common/CommonFunctions.h"

const char* dayOfWeekString(const struct CalendarCache* const restrict cache, const long udn) {
    return cache->dow.names[ modulus(udn,7) ];
}

int dayOfWeekISO(const long udn) {
    const int mod = modulus(udn,7);
    // this puts Saturday at 0 and Friday at 6
    // we want Monday at 1 and Sunday at 7
    // (Monday is 2 after the modulus)
    return (mod >= 2) ? (mod-1) : (mod+6);
}