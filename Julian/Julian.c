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

int JulianDecode(const struct CalendarCache* const restrict cache, long* output, const struct YMD* const restrict ymd) {
    // year zero is an issue
    if (ymd->year == 0 || ymd->month < 1 || ymd->month > 12) {
        return ERROR_VALIDATION;
    }
    // year and month numbers are valid
    long year = (ymd->year > 0) ? (ymd->year) : (ymd->year + 1);
    // year is a zero-adjusted year number
    if (year < -5879488 || year > 5879488) {
        return ERROR_BOUNDS;
        // -2147482992 is the smallest multiple of 1461 which
        // can fit in 32 bits
        // (-2147482992) / 1461 * 4 = -5879488
        // (2^31) - (1469872*1461) - 366 = 290
        // in 32 bits, we can fit 1469872 cycles of 4 years
        // 1469872*4+1 = 5879488
        // plus we can go to the end of that year
    }
    // we now know that the resulting udn will fit in
    // the signed 32-bit output
    long udn;
    // udn will be updated to hold the correct
    // universal date number
    {
        const int isLeapYear = (year % 4) ? 0 : 1;
        // we already checked the month number
        const int month = ymd->month - 1;
        const unsigned char* const monthLengths = isLeapYear ? &(cache->jgMonth.lengthLeap[0]) : &(cache->jgMonth.length[0]);
        if (ymd->day < 1 || ymd->day > monthLengths[month]) {
            return ERROR_VALIDATION;
        }
        // the day number is valid
        const unsigned short* const monthOffsets = isLeapYear ? &(cache->jgMonth.totalLeap[0]) : &(cache->jgMonth.total[0]);
        udn = monthOffsets[month] + (ymd->day - 1);
    }
    // udn is the number of days from the start of the year
    {
        const long yearInPeriod = modulus(year,4);
        // yearInPeriod is the number of years
        // since the start of the 4-year-period
        udn += ((year - yearInPeriod) / 4) * 1461;
        // (year - yearInPeriod) is the first year of the
        // 4-year-period, it is also divisible by 4
        // there are 1461 days in each 4-year-period
        year = yearInPeriod;
    }
    // udn is now the number of days from Julian Date 0
    // to the start of the 4-year-period
    // plus the number of days from the start of the year
    // to the current day
    // it is missing the number of days betweent the start of the
    // 4-year-period and the start of the year
    // year is now [0-3]
    if (year) {
        // year is 1,2, or 3
        --year;
        udn += 366;
        // first year is 366 days
        // year is 0,1, or 2
        udn += 365 * year;
    }
    // if year was 0
    // then the number of days from the start of the period
    // to the start of the year is 0
    // need to still convert from Julain Date to Universal Date
    *output = udn - 2;
    return NO_ERROR;
}