#ifndef __DOWCACHE_H__
#define __DOWCACHE_H__

struct DOWcache {
    const char* names[7];
};

void DOWcache__constructor(struct DOWcache* const restrict cache);

#endif