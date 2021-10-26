#include "YMD.h"

#include "CommonFunctions.h"
#include "ErrorCodes.h"

#include <stdlib.h>

UniversalCalendarErrorCode YMD__toString(const struct YMD* const restrict ymd, char** const restrict output, const char* const restrict prefix) {
    struct DynamicCharArray string;
    UniversalCalendarErrorCode e;
    e = DynamicCharArray__constructor(&string);
    if (e) {
        // if the constructor fails, then no memory is allocated
        // and there is no need to destruct
        return e;
    };
    // if the constructor succeeds, but there is a failure later
    // we will need to destruct
    e = DynamicCharArray__pushArray(&string,prefix);
    if (e) {
        free(string.data);
        return e;
    }
    e = DynamicCharArray__pushChar(&string,'(');
    if (e) {
        free(string.data);
        return e;
    }
    e = DynamicCharArray__pushIntegerChar(&string,ymd->year,',');
    if (e) {
        free(string.data);
        return e;
    }
    e = DynamicCharArray__pushIntegerChar(&string,ymd->month,',');
    if (e) {
        free(string.data);
        return e;
    }
    e = DynamicCharArray__pushIntegerChar(&string,ymd->day,')');
    if (e) {
        free(string.data);
        return e;
    }
    e = DynamicCharArray__pushChar(&string,0);
    if (e) {
        free(string.data);
        return e;
    }
    // the string should be fully constructed at this point
    // we can return it, the responsibility to destruct
    // is passed to the caller
    *output = string.data;
    return NO_ERROR;
}