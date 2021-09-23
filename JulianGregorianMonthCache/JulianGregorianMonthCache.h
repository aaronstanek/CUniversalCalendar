#ifndef __JULIANGREGORIANMONTHCACHE_H__
#define __JULIANGREGORIANMONTHCACHE_H__

struct JulianGregorianMonthCache {
    unsigned char length[12];
    unsigned char lengthLeap[12];
    unsigned short total[12];
    unsigned short totalLeap[12];
};

void JulianGregorianMonthCache__constructor(struct JulianGregorianMonthCache* const restrict cache);

#endif