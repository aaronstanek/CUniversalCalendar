#include "CommonFunctions.h"
#include "ErrorCodes.h"

#include <stdlib.h>
#include <limits.h>
#include <string.h>

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

UniversalCalendarErrorCode DynamicCharArray__grow(struct DynamicCharArray* const restrict a) {
    if (a->allocatedSize > INT_MAX-(a->allocatedSize)) {
        return ERROR_MEMORY;
    }
    const int new_allocatedSize = 2 * (a->allocatedSize);
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

UniversalCalendarErrorCode DynamicCharArray__push(struct DynamicCharArray* const restrict a, const char c) {
    if (a->logicalSize == a->allocatedSize) {
        const UniversalCalendarErrorCode e = DynamicCharArray__grow(a);
        if (e) return e;
    }
    // there is enough space to save another char
    a->data[a->logicalSize] = c;
    ++(a->logicalSize);
    return NO_ERROR;
}

UniversalCalendarErrorCode DynamicCharArray__pushArray(struct DynamicCharArray* const restrict a, const char* const restrict c) {
    // c must be a null-terminated array
    for (int i = 0; 1; ++i) {
        const char elem = c[i];
        if (elem) {
            const UniversalCalendarErrorCode e = DynamicCharArray__push(a,elem);
            if (e) return e;
        }
        else {
            return NO_ERROR;
        }
    }
}

UniversalCalendarErrorCode DynamicCharArray__pushInteger(struct DynamicCharArray* const restrict a, const int_fast32_t number) {
    struct IntToString intAsString;
    {
        const UniversalCalendarErrorCode e = IntToString__constructor(&intAsString,number);
        if (e) return e;
    }
    return DynamicCharArray__pushArray(a,&(intAsString.letters[0]));
}

UniversalCalendarErrorCode DynamicCharArray__pushIntegerChar(struct DynamicCharArray* const restrict a, const int_fast32_t number, const char c) {
    {
        const UniversalCalendarErrorCode e = DynamicCharArray__pushInteger(a,number);
        if (e) return e;
    }
    return DynamicCharArray__push(a,c);
}