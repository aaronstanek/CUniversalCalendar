#include "CommonFunctions.h"
#include "ErrorCodes.h"

#include <stdlib.h>

uint_fast32_t searchSumArray32(const uint_least32_t* const restrict array, uint_fast32_t highestIndex, const uint_fast32_t target) {
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

uint_fast32_t searchSumArray16(const uint_least16_t* const restrict array, uint_fast32_t highestIndex, const uint_fast16_t target) {
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

UniversalCalendarErrorCode IntToString__constructor(struct IntToString* const restrict output, int_fast32_t n) {
    if (n > 2147483647 || n < -2147483647) {
        return ERROR_BOUNDS;
    }
    else if (n == 0) {
        output->letters[0] = '0';
        output->letters[1] = 0;
        return NO_ERROR;
    }
    else {
        int is_negative;
        if (n < 0) {
            is_negative = 1;
            n *= -1;
        }
        else {
            is_negative = 0;
        }
        // n is positive now
        int index = 11;
        while (n) {
            output->letters[index] = (n % 10) + '0';
            index -= 1;
            n /= 10;
        }
        // output is loaded with the abs of n
        // index is before the first defined character
        // but still >= 0
        if (is_negative) {
            output->letters[index] = '-';
            is_negative = 0;
        }
        else {
            ++index;
        }
        // index points to the first defined character
        // is_negative is zero
        // reuse is_negative to keep track
        // of the writing location as we copy all the bytes forward
        // the last defined byte is at index=11
        while (index < 12) {
            output->letters[is_negative] = output->letters[index];
            ++is_negative;
            ++index;
        }
        // we know that the string can have length
        // at most 11,
        // so we are always safe in placing a terminal 0
        // is_negative is after the last defined character
        output->letters[is_negative] = 0;
        return NO_ERROR;
    }
}

UniversalCalendarErrorCode DynamicCharArray__constructor(struct DynamicCharArray* const restrict a) {
    a->data = malloc(32);
    if (a->data) {
        a->allocatedSize = 32;
        a->logicalSize = 0;
        return NO_ERROR;
    }
    else {
        return ERROR_MEMORY;
    }
}

UniversalCalendarErrorCode DynamicCharArray__grow(struct DynamicCharArray* const restrict a, const int new_allocatedSize) {
    char* const restrict new_data = realloc(a->data,new_allocatedSize);
    if (new_data) {
        a->data = new_data;
        a->allocatedSize = new_allocatedSize;
        return NO_ERROR;
    }
    else {
        return ERROR_MEMORY;
    }
}

UniversalCalendarErrorCode DynamicCharArray__pushChar(struct DynamicCharArray* const restrict a, const char c) {
    if (a->logicalSize == a->allocatedSize) {
        const UniversalCalendarErrorCode e = DynamicCharArray__grow(a,2*(a->allocatedSize));
        if (e) return e;
    }
    // there is enough space to save another char
    a->data[a->logicalSize] = c;
    ++(a->logicalSize);
    return NO_ERROR;
}

UniversalCalendarErrorCode DynamicCharArray__pushArrayWithSize(struct DynamicCharArray* const restrict a, const char* const restrict c, const int len) {
    const int new_logicalSize = a->logicalSize + len;
    if (new_logicalSize > a->allocatedSize) {
        // we need to grow the array
        int new_allocatedSize = a->allocatedSize;
        do {
            new_allocatedSize *= 2;
        } while (new_logicalSize > new_allocatedSize);
        const UniversalCalendarErrorCode e = DynamicCharArray__grow(a,new_allocatedSize);
        if (e) return e;
    }
    // there is enough space to copy the array
    memcpy(&(a->data[a->logicalSize]),c,len);
    a->logicalSize = new_logicalSize;
    return NO_ERROR;
}