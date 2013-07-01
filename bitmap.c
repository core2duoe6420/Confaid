#include <stdlib.h>
#include <assert.h>
#include <glib.h>

#include "bitmap.h"

struct bitmap * bitmap_create(struct bitmap * bm, unsigned int bits_nr) {
    int byte_nr = (bits_nr + 7) / 8;
    int alloc_bm = 0;
    if(bm == NULL) {
        bm = (struct bitmap *)g_malloc(sizeof(struct bitmap));
        alloc_bm = 1;
    }

    assert(bm);

    bm->bits = (char *)g_malloc0(byte_nr * sizeof(char));

    assert(bm->bits);

    bm->last_usable = 0;
    bm->bits_nr = bits_nr;
    bitmap_count_usable(bm);
    return bm;
}

int bitmap_count_usable(struct bitmap * bm)
{
    bm->usable = 0;
    for(int i = 0; i < bm->bits_nr; i++)
        if(bitmap_test(bm, i) == 0)
            bm->usable++;

    return bm->usable;
}

//获得第一个可用单位的同时会将该位置1，即标记为已用
int bitmap_get_first_usable(struct bitmap * bm)
{
    if(bm->usable == 0)
        return BITMAP_FULL;

    for(int i = bm->last_usable; i < bm->bits_nr; i++) {
        if(bitmap_test(bm, i) == 0) {
            bm->last_usable = i;
            bitmap_set(bm, i);
            return i;
        }
    }
    for(int i = 0; i < bm->last_usable; i++) {
        if(bitmap_test(bm, i) == 0) {
            bm->last_usable = i;
            bitmap_set(bm, i);
            return i;
        }
    }
    return BITMAP_FULL;
}

void bitmap_clean(struct bitmap * bm)
{
    if(bm->bits)
        g_free(bm->bits);
    bm->bits_nr = 0;
    bm->last_usable = 0;
    bm->usable = 0;
}

void bitmap_destroy(struct bitmap * bitmap)
{
    g_free(bitmap->bits);
    g_free(bitmap);
}

char bitmap_test(struct bitmap * bm, int bit)
{
    int idx, rem;
    idx = bit / 8;
    rem = bit % 8;
    return bm->bits[idx] & (1 << rem);
}

void bitmap_set(struct bitmap * bm, int bit)
{
    int idx, rem;
    idx = bit / 8;
    rem = bit % 8;
    bm->bits[idx] |= 1 << rem;
    bm->usable--;
}

void bitmap_clear(struct bitmap* bm, int bit)
{
    int idx, rem;
    idx = bit / 8;
    rem = bit % 8;
    bm->bits[idx] &= ~(1 << rem);
    bm->usable++;

    //bm->last_usable = bit;
}