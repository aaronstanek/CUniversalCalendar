#include "CommonFunctions.h"
#include "ErrorCodes.h"

#include "limits.h"

int checkForOverflow(const long a, const long b) {
    // make sure that we can add a and b without overflow
    if (a >= 0) {
        // a is nonnegative
        if (b > 0) {
            // b is positive
            // need to check the positive bound
            // LONG_MAX - a is the largest value
            // that can be added to a without overflow
            if (b > LONG_MAX - a) {
                return ERROR_BOUNDS;
            }
        }
    }
    else {
        // a is negative
        if (b < 0) {
            // b is negative
            // need to check the negative bound
            // LONG_MIN - a is the smallest value
            // that can be added to a without underflow
            if (b < LONG_MIN - a) {
                return ERROR_BOUNDS;
            }
        }
    }
    // either a and b have opposite signs and
    // we don't need to check
    // or we did check and they passed
    return NO_ERROR;
}

unsigned long searchSumArrayLong(const unsigned long* const restrict array, unsigned long highestIndex, const unsigned long target) {
    unsigned long lowestIndex = 0;
    do {
        const unsigned long middleIndex = (lowestIndex + highestIndex) / 2;
        if (target >= array[middleIndex]) {
            lowestIndex = middleIndex;
        }
        else {
            highestIndex = middleIndex;
        }
    } while (highestIndex-lowestIndex > 1);
    return (target >= array[highestIndex]) ? highestIndex : lowestIndex;
}

unsigned long searchSumArrayShort(const unsigned short* const restrict array, unsigned long highestIndex, const unsigned short target) {
    unsigned long lowestIndex = 0;
    do {
        const unsigned long middleIndex = (lowestIndex + highestIndex) / 2;
        if (target >= array[middleIndex]) {
            lowestIndex = middleIndex;
        }
        else {
            highestIndex = middleIndex;
        }
    } while (highestIndex-lowestIndex > 1);
    return (target >= array[highestIndex]) ? highestIndex : lowestIndex;
}