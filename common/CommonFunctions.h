#ifndef __COMMON_FUNCTIONS_H__
#define __COMMON_FUNCTIONS_H__

#include "ErrorType.h"

#include <stdint.h>
#include <string.h>

inline int_fast32_t modulus(int_fast32_t a, const int_fast32_t b) {
    // C defines a % b as a - (a/b)*b.
    // this works fine for nonnegative values
    // but has implementaion-defined behavior
    // when a is negative.
    // let a be anything, let b be greater than zero.

    #if (-1) / 5 == -1
    // division rounds down
    // this case is easy.
    // (a/b)*b will give the largest multiple
    // of b less than or equal to a.
    // so % always returns the modulus.
    return a % b;
    #else
    // division rounds to zero
    // this case is a bit harder.
    // for nonnegative a, this works
    // identically to the case above.
    // for negative a, % will yield
    // a nonpositive value (-b,0].
    a %= b;
    // at this point, a >= 0 will be the
    // correct output
    // a < 0 will need b added to get to
    // the correct output
    return ( a >= 0 ) ? a : ( a + b );
    #endif
}

uint_fast32_t searchSumArray32(const uint_least32_t* const restrict array, uint_fast32_t highestIndex, const uint_fast32_t target);

uint_fast32_t searchSumArray16(const uint_least16_t* const restrict array, uint_fast32_t highestIndex, const uint_fast16_t target);

struct IntToString {
    char letters[12];
};

UniversalCalendarErrorCode IntToString__constructor(struct IntToString* const restrict output, int_fast32_t n);

struct DynamicCharArray {
    char* data;
    int allocatedSize;
    int logicalSize;
};

UniversalCalendarErrorCode DynamicCharArray__constructor(struct DynamicCharArray* const restrict a);

UniversalCalendarErrorCode DynamicCharArray__pushChar(struct DynamicCharArray* const restrict a, const char c);

UniversalCalendarErrorCode DynamicCharArray__pushArrayWithSize(struct DynamicCharArray* const restrict a, const char* const restrict c, const int len);

inline UniversalCalendarErrorCode DynamicCharArray__pushArray(struct DynamicCharArray* const restrict a, const char* const restrict c) {
    // c must be a null terminated array
    return DynamicCharArray__pushArrayWithSize(a,c,strlen(c));
}

inline UniversalCalendarErrorCode DynamicCharArray__pushInteger(struct DynamicCharArray* const restrict a, const int_fast32_t number) {
    struct IntToString intAsString;
    {
        const UniversalCalendarErrorCode e = IntToString__constructor(&intAsString,number);
        if (e) return e;
    }
    return DynamicCharArray__pushArray(a,&(intAsString.letters[0]));
}

inline UniversalCalendarErrorCode DynamicCharArray__pushIntegerChar(struct DynamicCharArray* const restrict a, const int_fast32_t number, const char c) {
    {
        const UniversalCalendarErrorCode e = DynamicCharArray__pushInteger(a,number);
        if (e) return e;
    }
    return DynamicCharArray__pushChar(a,c);
}

#endif