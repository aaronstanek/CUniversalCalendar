#ifndef __COMMON_FUNCTIONS_H__
#define __COMMON_FUNCTIONS_H__

inline long modulus(long a, const long b) {
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

int checkForOverflow(const long a, const long b);

unsigned long searchSumArrayLong(const unsigned long* const restrict array, unsigned long highestIndex, const unsigned long target);

unsigned long searchSumArrayShort(const unsigned short* const restrict array, unsigned long highestIndex, const unsigned short target);

#endif