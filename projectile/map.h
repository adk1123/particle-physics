#ifndef MAP
#define MAP
#include <stdint.h>

typedef struct Entry {

    char *key;
    double value;
    struct Entry *next;

} Entry;

typedef struct {

    Entry **buckets;
    size_t count;
    size_t capacity;

} HashMap;


#endif