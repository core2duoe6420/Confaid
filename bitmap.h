#ifndef __BITMAP_H
#define __BITMAP_H

#include <stddef.h>

#define BITMAP_FULL -1

struct bitmap {
    char * bits;
    size_t bits_nr;
    int last_usable;
    int usable;
};

struct bitmap * bitmap_create(struct bitmap * bm, unsigned int bits_nr);
void bitmap_destroy(struct bitmap * bitmap);
void bitmap_clean(struct bitmap * bm);
char bitmap_test(struct bitmap * bm, int bit);
void bitmap_set(struct bitmap * bm, int bit);
void bitmap_clear(struct bitmap* bm, int bit);
int bitmap_get_first_usable(struct bitmap * bm);
int bitmap_count_usable(struct bitmap * bm);

#endif