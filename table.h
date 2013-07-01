#ifndef __TABLE_H
#define __TABLE_H

#include "database.h"

#define COL_INT 1
#define COL_DOUBLE 2
#define COL_CHAR 3

struct column {
    int c_type;
    int c_size;
    int c_notnull;
    int c_pri_key;
    char c_name[NAMEMAX_LEN + 1];
    char c_tbname[NAMEMAX_LEN + 1];
    char c_dbname[NAMEMAX_LEN + 1];
    int c_offset;
    char c_fk_tbname[NAMEMAX_LEN + 1];
    char c_fk_colname[NAMEMAX_LEN + 1];
    int c_unique;
};

struct table {
    char tb_name[NAMEMAX_LEN + 1];
    struct database * tb_db;
    struct column * tb_cols;
    int tb_col_nr;
    int tb_record_size;
    //struct record * tb_record;
    struct table * tb_next;
};

struct record {
    char * data;
    struct rnode_m * rnode;
    struct table * table;
    size_t size;
};

struct table * table_create(struct database * db, char * tb_name, int colnr, int rec_size);
struct table * table_new_instance(struct database * db, char * db_name, int colnr);
struct table * table_get_by_name(struct database * db, char * tb_name);

struct block * table_get_block(struct table * tb);
int table_column_get_id_by_name(struct table * tb, char * col_name);
struct column * table_get_column(struct table * tb, char * col_name);

struct record * record_new_instance(struct table * tb);
void record_bind_rnode(struct record * rec, struct rnode_m * rn);
void record_destroy(struct record * rec);
void record_write_buffer(struct record * rec);
void record_read_buffer(struct record * rec);

void record_column_set_value(struct record * rec, int col_id, void * value);
void record_column_set_value_by_name(struct record * rec, char * colname, void * value);
void * record_column_get_value(struct record * rec, int col_id);
void * record_column_get_value_by_name(struct record * rec, char * colname);
int record_alloc_piece(struct record * rec);

int table_insert_record(struct table * tb, ...);

void table_print_column(struct table * tb, int colnr, ...);
#endif