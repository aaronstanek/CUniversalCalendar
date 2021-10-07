#include "CommonFunctions.h"
#include "ErrorCodes.h"

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