#include "Gregorian.h"

#include "../common/CommonFunctions.h"
#include "../common/ErrorCodes.h"

inline int GregorianLeapYear(const int_fast32_t year) {
    // year is zero-adjusted
    // year = 0 corresponds to 1 BCE
    // year = -1 corresponds to 2 BCE
    if ( year % 4 ) {
        // not divisible by 4
        // can't be a leap year
        return 0;
    }
    else if ( year % 100 ) {
        // divisible by 4, but not by 100,
        // it's a leap year
        return 1;
    }
    else if ( year % 400 ) {
        // divisible by 100, but not 400,
        // it's not a leap year
        return 0;
    }
    else {
        // divisible by 400
        // leap year
        return 1;
    }
}

UniversalCalendarErrorCode GregorianEncode(const struct CalendarCache* const restrict cache, struct YMD* const restrict output, const int_fast32_t udn) {
    if (udn < -2147479803) {
        // -2147479803 = 146097 * (-14699)
        // the smallest negative multiple
        // of 146097 which can fit in 32 signed bits
        return ERROR_BOUNDS;
    }

    int_fast32_t n; // temp variable
    int isStandard; // temp variable

    n = modulus(udn,146097);
    // n is the number of days since the beginning
    // of a quadCentury (400 years, starting with a century leap year)
    // 0 <= n < 146097
    // 146097 is the number of days in a quadCentury

    int_fast32_t year = ((udn - n) / 146097) * 400;
    // udn - n is a multiple of 146097
    // the variable "year", doesn't actually tell us the exact year.
    // instead it tells us the first year of the quadCentury
    // we are in

    if (n < 36525) {
        // we are in the first century of the quadCentury
        // we don't have to adjust the number of years
        // to match the century
        // we can go directly to handling 4 year periods
        // all of which are standard in this century
        isStandard = 1;
    }
    else {
        // we are in the 2nd, 3rd, or 4th
        // century of the quadCentury
        year += 100;
        n -= 36525;
        // we have now moved to the first day of the
        // 2nd century
        const int_fast32_t centuries = n / 36524;
        year += 100 * centuries;
        n -= 36524 * centuries;
        // we are now at the start of the current
        // century
        // the first 4 years are short
        // all others are normal
        if (n < 1460) {
            // we are in a short
            // 4 year period
            isStandard = 0;
        }
        else {
            // get rid of the short 4 years
            year += 4;
            n -= 1460;
            // all the rest can be handled normally
            isStandard = 1;
        }
    }

    // isStandard = 1 means that we are at the start of a block
    // of standard 4-year units (1 leap, 3 normal)
    // isStandard = 0 means that we are at the start of a single
    // block of 4 short (non-leap) years

    if (isStandard) {
        // every 4 years is a leap year here
        // count how many 4-year periods since the
        // most recent reference point
        // 1461 days in each 4-year period
        const int_fast32_t fourYearPeriods = n / 1461;
        year += 4 * fourYearPeriods;
        n -= 1461 * fourYearPeriods;
        // year is the most recent leap year
        // n is how many days since the start
        // of that leap year
        if (n < 366) {
            // we are in the first year
            // don't need to update anything
            // but we do need to indicate that this
            // is not a standard year length
            isStandard = 0;
        }
        else {
            // we are in the 2nd, 3rd, or 4th
            // years
            ++year;
            n -= 366;
            // we are at the start of the standard length years
            // isStandard is already set to 1
        }
    }
    else {
        // short 4 year period
        // all years are standard here
        isStandard = 1;
    }

    // isStandard = 1 means that we are at the start of a block of
    // multiple years, none of which are leap years
    // isStandard = 0 means that we are at the start of a leap year

    const uint_least16_t* monthOffsetArray;
    if (isStandard) {
        // we have only short years here
        // each year has 365 days
        const int_fast32_t years = n / 365;
        year += years;
        n -= 365 * years;
        // we are at the start of a standard year
        // year is correctly set
        monthOffsetArray = &(cache->jgMonth.total[0]);
    }
    else {
        // we are at the start of a leap year
        // year is correctly set
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

UniversalCalendarErrorCode GregorianDecode(const struct CalendarCache* const restrict cache, int_fast32_t* output, const struct YMD* const restrict ymd) {
    // year zero is an issue
    if (ymd->year == 0 || ymd->month < 1 || ymd->month > 12) {
        return ERROR_VALIDATION;
    }
    // year and month numbers are valid
    int_fast32_t year = (ymd->year > 0) ? (ymd->year) : (ymd->year + 1);
    // year is a zero-adjusted year number
    if (year < -5879600 || year > 5879609) {
        return ERROR_BOUNDS;
        // -5879600 / 400 = -14699
        // -14699 * 146097 = -2147479803
        // if we allow any smaller year
        // then we will need to use
        // a udn smaller than -(2^-31-1)
        // 5879609 / 400 = 14699
        // 14699 * 146097 = 2147479803
        // that's the start of the year 5879600
        // the end of 5879609 will be
        // (366 + 365 + 365 + 365) * 2 + (366+365)
        // days later, coming up about 6 months before
        // the (2^31-1) limit
    }
    // we now know that the resulting udn will fit in
    // the signed 32-bit output
    int_fast32_t udn;
    // udn will be updated to hold the correct
    // universal date number
    {
        const int isLeapYear = GregorianLeapYear(year);
        // we already checked the month number
        const int month = ymd->month - 1;
        const uint_least8_t* const monthLengths = isLeapYear ? &(cache->jgMonth.lengthLeap[0]) : &(cache->jgMonth.length[0]);
        if (ymd->day < 1 || ymd->day > monthLengths[month]) {
            return ERROR_VALIDATION;
        }
        // the day number is valid
        const uint_least16_t* const monthOffsets = isLeapYear ? &(cache->jgMonth.totalLeap[0]) : &(cache->jgMonth.total[0]);
        udn = monthOffsets[month] + (ymd->day - 1);
    }
    // udn holds the number of days since the start of the year
    {
        const int_fast32_t yearInQuadCentury = modulus(year,400);
        udn += ((year - yearInQuadCentury) / 400 ) * 146097;
        // year - yearInQuadCentury is the first year
        // of the quadcentury (multiple of 400)
        // dividing my 400 gives the index of the quadcentry
        // 146097 days per quadcentury
        year = yearInQuadCentury;
    }
    // year is [0-400)
    // udn is set to the first day of this quadcentury
    // plus the number of days since the start of the year
    // it is missing the number of days from the start of
    // the quadcentury to the start of the year
    int isStandard;
    if (year < 100) {
        isStandard = 0;
    }
    else {
        isStandard = 1;
        // we need to subtract years
        // and add days to get year less than 100
        // the first century has an extra day
        year -= 100;
        udn += 36525; // number of days in a long century
        // year is [0-300)
        const int_fast32_t centuries = year / 100;
        year -= 100 * centuries;
        udn += 36524 * centuries;
    }
    // year is [0,100)
    // udn is set to the start of this century
    // plus the number of days since the start of the year
    // isStandard = 1 means that this century starts with a standard year
    // isStandard = 0 means that this century starts with a leap year
    if (isStandard) {
        // the first year of the century
        // is not a leap year
        if (year < 4) {
            isStandard = 0;
        }
        else {
            year -= 4;
            udn += 1460;
            // we now start a sequence where
            // every 4th year is a leap year
            // isStandard is already 1
        }
    }
    else {
        // the first year of the century is
        // a leap year
        isStandard = 1;
    }
    // isStandard = 0 means that year < 4
    // and all the years are standard
    // isStandard = 1 means that year < 100
    // and all the years divisible by 4
    // are leap years
    if (isStandard) {
        const int_fast32_t fourYearPeriods = year / 4;
        year -= 4 * fourYearPeriods;
        udn += 1461 * fourYearPeriods;
        // year < 4
        // the first year is a leap year
        if (year) {
            year -= 1;
            udn += 366;
            // the remainder are standard years
            udn += 365 * year;
        }
        // if year is zero, then we don't need to add anything
    }
    else {
        // year < 4
        // all the years are 365 days long
        udn += 365 * year;
    }
    // udn is set correctly
    *output = udn;
    return NO_ERROR;
}

UniversalCalendarErrorCode GregorianToString(const struct YMD* const restrict ymd, char** const restrict output) {
    return YMD__toString(ymd,output,"GregorianDate");
}