#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <glib.h>

#include "table.h"
#include "rnode.h"

struct record * record_new_instance(struct table * tb) {
    struct record * rec;
    int size = tb->tb_record_size;
    rec = (struct record *)g_malloc(sizeof(struct record));
    assert(rec);

    rec->data = (char *)g_malloc(size);
    assert(rec->data);

    rec->table = tb;
    rec->size = size;
    rec->rnode = NULL;
    return rec;
}

void record_bind_rnode(struct record * rec, struct rnode_m * rn)
{
    rec->rnode = rn;
}

//仅仅释放内存！不会对rnode进行任何操作！
void record_destroy(struct record * rec)
{
    g_free(rec->data);
    g_free(rec);
}

//返回分配的片数，等于0说明出错
int record_alloc_piece(struct record * rec)
{
    assert(rec->rnode);
    //不应该为已经分配过的rnode分配空间
    assert(rec->rnode->r_node.r_zone[0] == 0);

    int size = rec->table->tb_record_size;
    int count = 0;
    while(size > 0) {
        if(rnode_alloc_piece(rec->rnode) == 0)
            return 1;
        size -= rec->rnode->r_block->header.piece_size;
        count++;
    }
    return count;
}

#define RECORD_READ 1
#define RECORD_WRITE 2

static void _record_op_buffer(struct record * rec, int op)
{
    assert(rec->rnode);

    struct piece * datap = NULL, * idxp = NULL;
    struct rnode_m * rn = rec->rnode;
    struct block * b = rn->r_block;
    int * arridx = rn->r_node.r_zone;
    int item = RNODE_ITEM - 1;
    int offset = 0, size = 0, remain = rec->size;
    int piece_size = b->header.piece_size;

    int i = 0;
    while(remain) {
        int pid;
        pid = arridx[i];
        assert(pid);
        //索引项
        if(i == item) {
            if(idxp)
                piece_destroy(idxp);
            idxp = piece_new_instance(b, pid);
            piece_read_buffer(idxp);
            arridx = (int *)idxp->p_data;
            item = piece_size / sizeof(int) - 1;
            i = 0;
            continue;
        }

        size = remain > piece_size ? piece_size : remain;

        datap = piece_new_instance(b, pid);

        if(op == RECORD_WRITE) {
            //写
            memcpy(datap->p_data, rec->data + offset, size);
            piece_write_buffer(datap);
        } else if(op == RECORD_READ) {
            //读
            piece_read_buffer(datap);
            memcpy(rec->data + offset, datap->p_data, size);
        }

        piece_destroy(datap);

        offset += size;
        remain -= size;

        i++;
    }
}

void record_write_buffer(struct record * rec)
{
    _record_op_buffer(rec, RECORD_WRITE);
}

void record_read_buffer(struct record * rec)
{
    _record_op_buffer(rec, RECORD_READ);
}

int table_column_get_id_by_name(struct table * tb, char * col_name)
{
    for(int i = 0; i < tb->tb_col_nr; i++) {
        if(strcmp(tb->tb_cols[i].c_name, col_name) == 0)
            return i;
    }
    return -1;
}

struct column * table_get_column(struct table * tb, char * col_name) {
    for(int i = 0; i < tb->tb_col_nr; i++) {
        if(strcmp(tb->tb_cols[i].c_name, col_name) == 0)
            return &tb->tb_cols[i];
    }
    return NULL;
}

void record_column_set_value(struct record * rec, int col_id, void * value)
{
    struct column * col;
    col = &rec->table->tb_cols[col_id];

    int offset = col->c_offset;
    int size = col->c_size;
    int need_free = 0;

    if(value == NULL) {
        value = g_malloc(size);
        need_free = 1;
        switch(col->c_type) {
        case COL_INT:
            *(int*)value = INT_NULL;
            break;
        case COL_DOUBLE:
            *(double*)value = DOUBLE_NULL;
            break;
        case COL_CHAR:
            strcpy((char*)value, CHAR_NULL);
            break;
        }
    }

    memcpy(rec->data + offset, value, size);
    if(need_free)
        g_free(value);
}

void record_column_set_value_by_name(struct record * rec, char * colname, void * value)
{
    int id = table_column_get_id_by_name(rec->table, colname);
    record_column_set_value(rec, id, value);
}

void * record_column_get_value(struct record * rec, int col_id)
{
    int offset = rec->table->tb_cols[col_id].c_offset;
    return rec->data + offset;
}

void * record_column_get_value_by_name(struct record * rec, char * colname)
{
    int col_id = table_column_get_id_by_name(rec->table, colname);
    int offset = rec->table->tb_cols[col_id].c_offset;
    return rec->data + offset;
}

struct table * table_new_instance(struct database * db, char * db_name, int colnr) {
    struct table * tb;
    tb = (struct table *)g_malloc(sizeof(struct table));
    assert(tb);

    tb->tb_db = db;
    strcpy(tb->tb_name, db_name);
    tb->tb_col_nr = colnr;
    tb->tb_next = NULL;
    tb->tb_record_size = 0;
    tb->tb_cols = (struct column *)g_malloc0(tb->tb_col_nr * sizeof(struct column));
    assert(tb->tb_cols);

    if(db) {
        tb->tb_next = db->d_table;
        db->d_table = tb;
    }
    return tb;
}

struct block * table_get_block(struct table * tb) {
    struct block * b = tb->tb_db->d_block;
    while(b) {
        if(strcmp(b->header.tb_name, tb->tb_name) == 0)
            return b;
        b = b->prev;
    }
    return NULL;
}

int table_insert_record(struct table * tb, ...)
{
    struct block * b;
    struct rnode_m * rn;
    struct record * rec;
    b = table_get_block(tb);
    //block的片接近用完？
    while(b && b->bitmap.usable < tb->tb_record_size / b->header.piece_size + 2)
        b = b->tb_prev;

    assert(b);

    rn = rnode_get_usable(b);
    rec = record_new_instance(tb);
    record_bind_rnode(rec, rn);
    record_alloc_piece(rec);

    va_list ap;
    va_start(ap, tb);
    for(int i = 0; i < tb->tb_col_nr; i++)
        record_column_set_value(rec, i, va_arg(ap, void *));
    va_end(ap);

    record_write_buffer(rec);

    rnode_destroy(rn);
    record_destroy(rec);

    return 0;
}

struct table * table_get_by_name(struct database * db, char * tb_name) {
    struct table * tb = db->d_table;
    while(tb) {
        if(strcmp(tb->tb_name, tb_name) == 0)
            return tb;
        tb = tb->tb_next;
    }
    return NULL;
}

//获得大于等于n的最小的2的幂
static int get_powertwo(int n)
{
    int ret = 1;
    if(n <= 0)
        return 0;
    n--;
    while(n) {
        n >>= 1;
        ret <<= 1;
    }
    return ret;
}

//原始函数，会创建block，实例化table，但不会往数据字典里写信息！
struct table * table_create(struct database * db, char * tb_name, int colnr, int rec_size) {
    int piece_size = get_powertwo(rec_size);
    //片的大小至少是sizeof(struct block_header)
    if(piece_size < sizeof(struct block_header))
        piece_size = get_powertwo(sizeof(struct block_header));

    struct table * tb;
    struct block * b;
    tb = table_new_instance(db, tb_name, colnr);
    tb->tb_record_size = rec_size;

    b = database_create_block(db, tb_name, piece_size);

    return tb;
}

void table_print_column(struct table * tb, int colnr, ...)
{
    struct record * rec;
    struct rnode_m * rn;
    struct block * b = table_get_block(tb);
    rec = record_new_instance(tb);
    while(b) {
        rnode_iter_initial(b);
        while((rn = rnode_iter_block(b))) {
            struct column * col;
            record_bind_rnode(rec, rn);
            record_read_buffer(rec);

            va_list ap;
            va_start(ap, colnr);
            char * colname;
            void * value;
            for(int i = 0; i < colnr; i++) {
                colname = va_arg(ap, char *);
                col = &tb->tb_cols[table_column_get_id_by_name(tb, colname)];
                value = record_column_get_value_by_name(rec, colname);
                switch(col->c_type) {
                case COL_INT:
                    printf("%d ", *(int*)value);
                    break;
                case COL_DOUBLE:
                    printf("%lf ", *(double*)value);
                    break;
                case COL_CHAR:
                    printf("%s ", value);
                    break;
                }
            }
            va_end(ap);

            printf("\n");
            rnode_destroy(rn);

        }
        b = b->tb_prev;
    }
    record_destroy(rec);
}