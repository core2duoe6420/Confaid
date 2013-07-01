#ifndef __BUFFER_H
#define __BUFFER_H

#include "datafile.h"

#define HASH_NR (1024 * 1024)

#include "bitmap.h"

struct buffer {
    char * b_data;
    struct datafile * b_df;
    int b_bid;
    int b_dirty;

    struct buffer * b_hash;
    struct buffer * b_lru_next;
    struct buffer * b_lru_prev;
    struct buffer * b_dirty_next;
    struct buffer * b_dirty_prev;
};

struct buffer_header {
    char * bh_data;
    size_t bh_block_size;
    size_t bh_buffer_size;
    int bh_buffer_max;
    int bh_buffer_using;
    struct bitmap bh_buf_map;
    struct buffer bh_list_head;
    struct buffer bh_list_tail;
};

int initial_buffer(size_t bufsize, size_t block_size);
void buffer_flush();
struct buffer * get_buffer_block(struct datafile * df, int offset);
void buffer_clear_dirty(struct buffer * buf);
void buffer_set_dirty(struct buffer * buf);
int structure_read_buffer(struct datafile * df, void * structure, size_t size, int offset);
int structure_write_buffer(struct datafile * df, void * structure, size_t size, int offset);

#endif