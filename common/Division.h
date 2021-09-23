#ifndef __DIVISION_H__
#define __DIVISION_H__

// check the rounding direction of division
// of a negative integer by a positive integer

#if (-1) / 5 == 0

#define DIVISION_ROUNDS_ZERO

#elif (-1) / 5 == -1

#define DIVISION_ROUNDS_DOWN

#else

#error (-1) / 5 must yield 0 or -1

#endif

#endif