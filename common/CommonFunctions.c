#include "CommonFunctions.h"
#include "ErrorCodes.h"

uint_fast32_t searchSumArrayLong(const uint_least32_t* const restrict array, uint_fast32_t highestIndex, const uint_fast32_t target) {
    uint_fast32_t lowestIndex = 0;
    do {
        const uint_fast32_t middleIndex = (lowestIndex + highestIndex) / 2;
        if (target >= array[middleIndex]) {
            lowestIndex = middleIndex;
        }
        else {
            highestIndex = middleIndex;
        }
    } while (highestIndex-lowestIndex > 1);
    return (target >= array[highestIndex]) ? highestIndex : lowestIndex;
}

uint_fast32_t searchSumArrayShort(const uint_least16_t* const restrict array, uint_fast32_t highestIndex, const uint_fast16_t target) {
    uint_fast32_t lowestIndex = 0;
    do {
        const uint_fast32_t middleIndex = (lowestIndex + highestIndex) / 2;
        if (target >= array[middleIndex]) {
            lowestIndex = middleIndex;
        }
        else {
            highestIndex = middleIndex;
        }
    } while (highestIndex-lowestIndex > 1);
    return (target >= array[highestIndex]) ? highestIndex : lowestIndex;
}