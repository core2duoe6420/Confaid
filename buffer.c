#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <glib.h>

#include "buffer.h"

#define BUFFER_SIZE_DEFUALT (64*1024*1024)

int param_buffer_size = BUFFER_SIZE_DEFUALT;

struct buffer_header * global_bh = NULL;

struct buffer * hash_head[HASH_NR];

int buffer_hash(int offset)
{
    return offset / global_bh->bh_block_size % HASH_NR;
}

struct buffer_header * buffer_header_initial(size_t buf_size, size_t block_size) {
    struct buffer_header * bh;
    int buf_nr;
    bh = (struct buffer_header *)g_malloc(sizeof(struct buffer_header));

    assert(bh);

    buf_nr = buf_size / block_size;
    bh->bh_data = (char *)g_malloc(sizeof(char) * buf_size);

    assert(bh->bh_data);

    struct bitmap * bm;
    bm = bitmap_create(&bh->bh_buf_map, buf_nr);

    assert(bm);

    bh->bh_block_size = block_size;
    bh->bh_buffer_max = buf_nr;
    bh->bh_buffer_size = buf_size;
    bh->bh_buffer_using = 0;

    memset(&bh->bh_list_head, 0, sizeof(struct buffer));
    memset(&bh->bh_list_tail, 0, sizeof(struct buffer));
    bh->bh_list_head.b_dirty_next = &bh->bh_list_tail;
    bh->bh_list_head.b_lru_next = &bh->bh_list_tail;
    bh->bh_list_tail.b_dirty_prev = &bh->bh_list_head;
    bh->bh_list_tail.b_lru_prev = &bh->bh_list_head;

    return bh;
}

//在buffer_header中的data中取出block_size大小的一块
static char * _alloc_buffer_header(struct buffer_header * bh)
{
    if(bh->bh_buffer_using == bh->bh_buffer_max)
        return NULL;
    int idx = bitmap_get_first_usable(&bh->bh_buf_map);
    bh->bh_buffer_using++;
    return bh->bh_data + idx * bh->bh_block_size;
}

char * alloc_buffer_header()
{
    return _alloc_buffer_header(global_bh);
}

static void _release_buffer_header(struct buffer_header * bh, struct buffer * buf)
{
    int idx;
    idx = (buf->b_data - bh->bh_data) / bh->bh_block_size;
    bitmap_clear(&bh->bh_buf_map, idx);
    bh->bh_buffer_using--;
}

void release_buffer_header(struct buffer * buf)
{
    _release_buffer_header(global_bh, buf);
}

static void buffer_read_from_file(struct buffer * buf)
{
    fseek(buf->b_df->file, buf->b_bid * global_bh->bh_block_size, SEEK_SET);
    fread(buf->b_data, global_bh->bh_block_size, 1, buf->b_df->file);
}

static void buffer_write_to_file(struct buffer * buf)
{
    fseek(buf->b_df->file, buf->b_bid * global_bh->bh_block_size, SEEK_SET);
    fwrite(buf->b_data, global_bh->bh_block_size, 1, buf->b_df->file);
    fflush(buf->b_df->file);
}

static void buffer_dirty_delete(struct buffer * buf)
{
    struct buffer * prev, * next;
    prev = buf->b_dirty_prev;
    next = buf->b_dirty_next;
    assert(prev);
    assert(next);
    prev->b_dirty_next = next;
    next->b_dirty_prev = prev;
    buf->b_dirty_next = NULL;
    buf->b_dirty_prev = NULL;
}

static void buffer_dirty_insert(struct buffer * buf)
{
    if(buf->b_dirty_next || buf->b_dirty_prev)
        return;
    buf->b_dirty_next = global_bh->bh_list_head.b_dirty_next;
    global_bh->bh_list_head.b_dirty_next->b_dirty_prev = buf;
    global_bh->bh_list_head.b_dirty_next = buf;
    buf->b_dirty_prev = &global_bh->bh_list_head;
}

static struct buffer * buffer_dirty_del_tail() {
    struct buffer * tail;
    tail = global_bh->bh_list_tail.b_dirty_prev;
    buffer_dirty_delete(tail);
    return tail;
}

static void buffer_lru_delete(struct buffer * buf)
{
    struct buffer * prev, * next;
    prev = buf->b_lru_prev;
    next = buf->b_lru_next;
    assert(prev);
    assert(next);
    prev->b_lru_next = next;
    next->b_lru_prev = prev;
    buf->b_lru_next = NULL;
    buf->b_lru_prev = NULL;
}

static void buffer_lru_insert(struct buffer * buf)
{
    //已经在lru链表中？先删除
    if(buf->b_lru_next || buf->b_lru_prev)
        buffer_lru_delete(buf);
    buf->b_lru_next = global_bh->bh_list_head.b_lru_next;
    global_bh->bh_list_head.b_lru_next->b_lru_prev = buf;
    global_bh->bh_list_head.b_lru_next = buf;
    buf->b_lru_prev = &global_bh->bh_list_head;
}

static struct buffer * buffer_lru_del_tail() {
    struct buffer * tail;
    tail = global_bh->bh_list_tail.b_lru_prev;
    buffer_lru_delete(tail);
    return tail;
}

//buf不在hash表中可能会有bug，但目前测试正常
static void buffer_hashtable_delete(struct buffer * buf)
{
    int hashvalue = buffer_hash(buf->b_bid * global_bh->bh_block_size);
    struct buffer * prev = NULL, * hashptr = hash_head[hashvalue];
    while(hashptr && hashptr != buf) {
        prev = hashptr;
        hashptr = hashptr->b_hash;
    }
    if(prev)
        prev->b_hash = buf->b_hash;
    else
        hash_head[hashvalue] = buf->b_hash;

    buf->b_hash = NULL;
}

static void buffer_hashtable_insert(struct buffer * buf)
{
    int hashvalue = buffer_hash(buf->b_bid * global_bh->bh_block_size);
    buf->b_hash = hash_head[hashvalue];
    hash_head[hashvalue] = buf;
}

void buffer_delete(struct buffer * buf)
{
    //脏先写回
    assert(buf->b_data);
    if(buf->b_dirty) {
        buffer_write_to_file(buf);
        buf->b_dirty = 0;
        buffer_dirty_delete(buf);
    }
    if(buf->b_lru_next || buf->b_lru_prev)
        buffer_lru_delete(buf);

    buffer_hashtable_delete(buf);

    release_buffer_header(buf);

    g_free(buf);
}

void buffer_set_dirty(struct buffer * buf)
{
    if(buf->b_dirty)
        return;
    buf->b_dirty = 1;
    buffer_dirty_insert(buf);
}

void buffer_clear_dirty(struct buffer * buf)
{
    if(buf->b_dirty == 0)
        return;
    buf->b_dirty = 0;
    buffer_dirty_delete(buf);
}

void buffer_flush()
{
    while(global_bh->bh_list_head.b_dirty_next->b_data) {
        buffer_write_to_file(global_bh->bh_list_head.b_dirty_next);
        buffer_clear_dirty(global_bh->bh_list_head.b_dirty_next);
    }
}

struct buffer * buffer_get_instance() {
    struct buffer * buf;
    if(global_bh->bh_buffer_max == global_bh->bh_buffer_using)
        buffer_delete(global_bh->bh_list_tail.b_lru_prev);

    buf = (struct buffer *)g_malloc(sizeof(struct buffer));

    assert(buf);

    buf->b_data = alloc_buffer_header();

    buf->b_df = NULL;
    buf->b_bid = 0;
    buf->b_dirty = 0;
    buf->b_dirty_next = NULL;
    buf->b_dirty_prev = NULL;
    buf->b_hash = NULL;
    buf->b_lru_next = NULL;
    buf->b_lru_prev = NULL;

    memset(buf->b_data, 0, global_bh->bh_block_size);

    return buf;
}

static struct buffer * buffer_search_in_hashtable(struct datafile * df, int bid) {
    int hashvalue = buffer_hash(bid * global_bh->bh_block_size);
    struct buffer * buf;
    buf = hash_head[hashvalue];
    while(buf) {
        if(buf->b_bid == bid && buf->b_df == df)
            return buf;
        buf = buf->b_hash;
    }
    return NULL;
}

void buffer_bind_block(struct buffer * buf, struct datafile * df, int bid)
{
    buf->b_df = df;
    buf->b_bid = bid;
    buffer_hashtable_insert(buf);
}

//全局缓存初始化函数
int initial_buffer(size_t bufsize, size_t block_size)
{
    global_bh = buffer_header_initial(bufsize, block_size);
    //初始化全局变量
    for(int i = 0; i < HASH_NR; i++)
        hash_head[i] = NULL;

    return 0;
}

struct buffer * get_buffer_block(struct datafile * df, int offset) {
    struct buffer * buf;
    int bid;
    bid = offset / global_bh->bh_block_size;
    //先查缓存
    buf = buffer_search_in_hashtable(df, bid);
    //命中
    if(buf)
        return buf;
    //不命中，分配缓存，从文件中读取
    buf = buffer_get_instance();
    buffer_bind_block(buf, df, bid);
    buffer_lru_insert(buf);
    buffer_read_from_file(buf);
    return buf;
}

int structure_read_buffer(struct datafile * df, void * structure, size_t size, int offset)
{
    struct buffer * buf;
    int remain, real_size;
    remain = global_bh->bh_block_size - offset % global_bh->bh_block_size;
    real_size = size > remain ? remain : size;

    buf = get_buffer_block(df, offset);
    memcpy(structure, buf->b_data + offset % global_bh->bh_block_size, real_size);

    return real_size;
}

int structure_write_buffer(struct datafile * df, void * structure, size_t size, int offset)
{
    struct buffer * buf;
    int remain, real_size;
    remain = global_bh->bh_block_size - offset % global_bh->bh_block_size;
    real_size = size > remain ? remain : size;

    buf = get_buffer_block(df, offset);

    memcpy(buf->b_data + offset % global_bh->bh_block_size, structure, real_size);
    buffer_set_dirty(buf);
    return real_size;
}