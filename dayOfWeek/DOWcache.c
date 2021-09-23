#include "DOWcache.h"

void DOWcache__constructor(struct DOWcache* const restrict cache) {
    cache->names[0] = "Saturday";
    cache->names[1] = "Sunday";
    cache->names[2] = "Monday";
    cache->names[3] = "Tuesday";
    cache->names[4] = "Wednesday";
    cache->names[5] = "Thursday";
    cache->names[6] = "Friday";
}