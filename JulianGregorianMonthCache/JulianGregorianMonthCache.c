#include "JulianGregorianMonthCache.h"

#include <string.h>

void JulianGregorianMonthCache__constructor(struct JulianGregorianMonthCache* const restrict cache) {
    // lengths of months in a standard year
    // January is month 0
    cache->length[0] = 31; // jan
    cache->length[1] = 28; // feb
    cache->length[2] = 31; // mar
    cache->length[3] = 30; // apr
    cache->length[4] = 31; // may
    cache->length[5] = 30; // jun
    cache->length[6] = 31; // jul
    cache->length[7] = 31; // aug
    cache->length[8] = 30; // sep
    cache->length[9] = 31; // oct
    cache->length[10] = 30; // nov
    cache->length[11] = 31; // dec

    // only February is different between a
    // standard year and a leap year
    // February is month 1
    memcpy( &(cache->lengthLeap[0]) , &(cache->length[0]) , 12*sizeof(unsigned char) );
    cache->lengthLeap[1] = 29;

    // day offsets in a standard year
    cache->total[0] = 0;
    for (int i = 1; i < 12; ++i) {
        cache->total[i] = cache->total[i-1] + cache->length[i-1];
    }

    // day offsets in a leap year
    // January and February are the same as
    // in a standard year
    memcpy( &(cache->totalLeap[0]) , &(cache->total[0]) , 2*sizeof(unsigned short) );
    // all other months are one greater
    // than their standard counterparts
    for (int i = 2; i < 12; ++i) {
        cache->totalLeap[i] = cache->total[i] + 1;
    }
}