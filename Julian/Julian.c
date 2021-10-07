#include "Julian.h"

#include "../common/CommonFunctions.h"
#include "../common/ErrorCodes.h"

int JulianEncode(const struct CalendarCache* const restrict cache, struct YMD* const restrict output, const long udn) {
    if (udn > 2147483645 || udn < -2147482994) {
        return ERROR_BOUNDS;
        // we need to be able to add 2 to get the Julian Date
        // (2^31-1) - 2 = 2147483645
        // we need to be able to represent the multiple of 1461
        // less than the Julian Date
        // -2147482992 is the smallest multiple of 1461 which
        // can fit in 32 bits
        // but we will add 2 before this value, so the actual limit
        // is -2147482994
    }
    long n = udn + 2;
    // n is the Julian Date Number
    long year;
    {
        const long nStar = modulus(n,1461);
        // nStar is how many days since
        // the start of the current 4-year-period
        year = 4 * ( (n-nStar) / 1461 );
        // (n-nStar) is the Julian Date of the start
        // of the current 4-year-period
        // it is a multiple of 1461
        n = nStar;
    }
    // year is now the starting year of the current
    // 4-year period
    // n is the number of days since the start of that period
    const unsigned short* monthOffsetArray;
    if (n >= 366) {
        // we are in the 2nd, 3rd, or 4th year
        // of the four-year period
        // the first year has 366 days
        ++year;
        n -= 366;
        const long years = n / 365;
        // years is 0, 1, or 2
        year += years;
        n -= 365 * years;
        // the current year is not a leap year
        monthOffsetArray = &(cache->jgMonth.total[0]);
    }
    else {
        // we are in the first year of the 4-year-period
        // it is a leap year
        monthOffsetArray = &(cache->jgMonth.totalLeap[0]);
    }

    int month = searchSumArrayShort(monthOffsetArray,11,n);
    int day = n - monthOffsetArray[month];

    // now output
    output->year = (year>0) ? year : (year-1);
    output->month = month + 1;
    output->day = day + 1;
    return NO_ERROR;
}