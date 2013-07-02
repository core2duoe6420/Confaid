#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <assert.h>

#include "sql.h"

struct column * table_set_get_column(GPtrArray * tableset, char * colname) {
    for(int i = 0; i < tableset->len; i++) {
        struct table * tb;
        tb = table_set_get_table(tableset, i);
        struct column * col;
        col = table_get_column(tb, colname);
        if(col)
            return col;
    }
    return NULL;
}

void table_set_add_table(GPtrArray * tableset, struct table * tb)
{
    g_ptr_array_add(tableset, tb);
}

void table_set_add_table_by_name(GPtrArray * tableset, struct database * db, char * tbname)
{
    struct table * tb;
    tb = table_get_by_name(db, tbname);
    table_set_add_table(tableset, tb);
}

struct table * table_set_get_table(GPtrArray * tableset, int tbidx) {
    return (struct table *)g_ptr_array_index(tableset, tbidx);
}

struct table * table_set_get_table_by_name(GPtrArray * tableset, char * tbname) {
    for(int i = 0; i < tableset->len; i++) {
        struct table * tb;
        tb = table_set_get_table(tableset, i);
        if(strcmp(tb->tb_name, tbname) == 0)
            return tb;
    }
    return NULL;
}

void column_set_add_column(GPtrArray * colset, struct column * col)
{
    g_ptr_array_add(colset, col);
}

struct column * column_set_add_column_by_name(GPtrArray * colset, GPtrArray * tbset,
        char * tbname, char * colname) {
    struct table * tb;
    struct column * col = NULL;
    for(int i = 0; i < tbset->len; i++) {
        tb = table_set_get_table(tbset, i);
        if(tbname == NULL || tbname[0] == 0 ||
           strcmp(tbname, tb->tb_name) == 0) {
            col = table_get_column(tb, colname);
            if(col)
                break;
        }
    }
    if(col)
        column_set_add_column(colset, col);

    return col;
}

struct column * column_set_get_column(GPtrArray * colset, int colidx) {
    return (struct column *)g_ptr_array_index(colset, colidx);
}

int column_set_get_column_id(GPtrArray * colset, struct column * col)
{
    for(int i = 0; i < colset->len; i++) {
        struct column * tmpcol;
        tmpcol = column_set_get_column(colset, i);
        if(tmpcol == col)
            return i;
    }
    return -1;
}

struct column * column_set_get_column_by_name(GPtrArray * colset, char * tbname, char * colname) {
    for(int i = 0; i < colset->len; i++) {
        struct column * col;
        col = column_set_get_column(colset, i);
        if(strcmp(col->c_name, colname) == 0 &&
           (tbname == NULL || strcmp(col->c_tbname, tbname) == 0))
            return col;
    }
    return NULL;
}

static void myg_row_struct_destroy(void * r)
{
    struct row_struct * row;
    row = (struct row_struct *)r;
    g_free(row->data);
    g_free(row);
}

struct dataset * dataset_new_instance() {
    struct dataset * ds;
    ds = (struct dataset *)g_malloc0(sizeof(struct dataset));
    assert(ds);

    ds->column_set = g_ptr_array_sized_new(16);
    assert(ds->column_set);
    ds->row_set = g_ptr_array_sized_new(32);
    assert(ds->row_set);
    g_ptr_array_set_free_func(ds->row_set, myg_row_struct_destroy);
    ds->row_size = 0;

    return ds;
}

void dataset_destroy(struct dataset * ds)
{
    g_ptr_array_free(ds->column_set, FALSE);
    g_ptr_array_free(ds->row_set, TRUE);
    g_free(ds);
}

static struct row_struct * row_struct_new_instance(struct dataset * ds) {
    struct row_struct * row;
    struct column * col;
    row = (struct row_struct *)g_malloc0(sizeof(struct row_struct));
    assert(row);

    int total_size = ds->column_set->len * sizeof(char *) + ds->row_size;

    row->data = (char**)g_malloc(total_size);
    assert(row->data);

    int offset = ds->column_set->len * sizeof(char*);
    for(int i = 0; i < ds->column_set->len; i++) {
        col = (struct column *)g_ptr_array_index(ds->column_set, i);
        row->data[i] = (char*)row->data + offset;
        offset += col->c_size;
    }
    return row;
}

void dataset_add_column(struct dataset * ds, struct column * col)
{
    column_set_add_column(ds->column_set, col);
    ds->row_size += col->c_size;
}

void dataset_add_column_set(struct dataset * ds, GPtrArray * colset)
{
    for(int i = 0; i < colset->len; i++) {
        struct column * col;
        col = column_set_get_column(colset, i);
        dataset_add_column(ds, col);
    }
}

struct row_struct * dataset_add_row(struct dataset * ds) {
    struct row_struct * row;
    row = row_struct_new_instance(ds);
    g_ptr_array_add(ds->row_set, row);

    return row;
}

struct row_struct * dataset_get_row(struct dataset * ds, int rowid) {
    struct row_struct * row;
    row = (struct row_struct *)g_ptr_array_index(ds->row_set, rowid);
    return row;
}

void * row_struct_get_value_by_id(struct row_struct * row, int colid)
{
    return row->data[colid];
}

void * row_struct_get_value(struct row_struct * row, GPtrArray * colset,
                            struct column * col)
{
    int colid = column_set_get_column_id(colset, col);
    assert(colid >= 0);
    return row_struct_get_value_by_id(row, colid);
}

void row_struct_set_single_value_by_id(struct row_struct * row, GPtrArray * colset,
                                       int colid, void * value)
{
    struct column * col;
    col = column_set_get_column(colset, colid);
    memcpy(row->data[colid], value, col->c_size);
}

int row_struct_set_single_value(struct row_struct * row, GPtrArray * colset,
                                struct column * col, void * value)
{
    int colid = column_set_get_column_id(colset, col);
    assert(colid >= 0);
    row_struct_set_single_value_by_id(row, colset, colid, value);
    return 0;
}

void row_struct_set_all_value(struct row_struct * row, GPtrArray * colset, ...)
{
    va_list ap;
    va_start(ap, colset);
    for(int i = 0; i < colset->len; i++)
        row_struct_set_single_value_by_id(row, colset, i, va_arg(ap, void *));
    va_end(ap);
}

struct dataset * dataset_traverse_table(struct table * tb, int copy_rnode, int colnr, ...) {
    struct dataset * ds;
    ds = dataset_new_instance();
    //SELECT *
    if(colnr == tb->tb_col_nr) {
        for(int i = 0; i < tb->tb_col_nr; i++) {
            struct column * col;
            col = &tb->tb_cols[i];
            dataset_add_column(ds, col);
        }
    } else {
        //投影
        va_list ap;
        va_start(ap, colnr);
        for(int i = 0; i < colnr; i++) {
            char * colname;
            struct column * col;
            colname = va_arg(ap, char *);
            col = &tb->tb_cols[table_column_get_id_by_name(tb, colname)];
            assert(col);
            dataset_add_column(ds, col);
        }
        va_end(ap);
    }

    struct record * rec;
    struct rnode_m * rn;
    struct block * b = table_get_block(tb);
    struct row_struct * row;


    rec = record_new_instance(tb);
    while(b) {
        rnode_iter_initial(b);
        while((rn = rnode_iter_block(b))) {
            //在结果表中建立新行的实例
            row = dataset_add_row(ds);
            record_bind_rnode(rec, rn);
            record_read_buffer(rec);

            void * value;

            for(int i = 0; i < ds->column_set->len; i++) {
                int colidx_in_srctable;
                struct column * col;
                col = column_set_get_column(ds->column_set, i);
                colidx_in_srctable = col - tb->tb_cols;
                value = record_column_get_value(rec, colidx_in_srctable);
                row_struct_set_single_value_by_id(row, ds->column_set, i, value);
            }

            if(copy_rnode)
                memcpy(&row->rnode, rn, sizeof(struct rnode_m));

            rnode_destroy(rn);
        }
        b = b->tb_prev;
    }
    return ds;
}

struct dataset * dataset_join(struct dataset * ds1, struct dataset * ds2) {
    struct dataset * newds;
    newds = dataset_new_instance();

    dataset_add_column_set(newds, ds1->column_set);
    dataset_add_column_set(newds, ds2->column_set);

    for(int ds1rowid = 0; ds1rowid < ds1->row_set->len; ds1rowid++) {
        for(int ds2rowid = 0; ds2rowid < ds2->row_set->len; ds2rowid++) {
            struct row_struct * newrow;
            newrow = dataset_add_row(newds);

            struct row_struct * ds1row, * ds2row;
            ds1row = dataset_get_row(ds1, ds1rowid);
            ds2row = dataset_get_row(ds2, ds2rowid);

            char * newrow_data_addr = newrow->data[0];
            char * ds1row_data_addr = ds1row->data[0];
            char * ds2row_data_addr = ds2row->data[0];

            memcpy(newrow_data_addr, ds1row_data_addr, ds1->row_size);
            newrow_data_addr += ds1->row_size;
            memcpy(newrow_data_addr, ds2row_data_addr, ds2->row_size);
        }
    }

    //注意！会摧毁ds1和ds2！！
    dataset_destroy(ds1);
    dataset_destroy(ds2);
    return newds;
}

struct dataset * dataset_projection(struct dataset * ds, GPtrArray * colset) {
    struct dataset * newds;
    newds = dataset_new_instance();
    dataset_add_column_set(newds, colset);

    for(int rowid = 0; rowid < ds->row_set->len; rowid++) {
        struct row_struct * row, * newrow;
        row = (struct row_struct *)g_ptr_array_index(ds->row_set, rowid);
        newrow = dataset_add_row(newds);
        for(int colid = 0; colid < colset->len; colid++) {
            void * value;
            struct column * col;
            col = column_set_get_column(colset, colid);
            value = row_struct_get_value(row, ds->column_set, col);
            row_struct_set_single_value(newrow, colset, col, value);
        }
    }

    //注意！会销毁ds！！！
    dataset_destroy(ds);
    return newds;
}

void dataset_print(struct dataset * ds)
{
    if(ds->result != 0) {
        printf("%s\n", ds->info);
        return;
    }

    struct column * col;
    for(int i = 0; i < ds->column_set->len; i++) {
        col = column_set_get_column(ds->column_set, i);
        printf("%10s ", col->c_name);
    }
    printf("\n");

    for(int rowid = 0; rowid < ds->row_set->len; rowid++) {
        struct row_struct * row;
        row = dataset_get_row(ds, rowid);
        for(int colid = 0; colid < ds->column_set->len; colid++) {

            void * value;
            col = column_set_get_column(ds->column_set, colid);
            value = row_struct_get_value_by_id(row, colid);
            switch(col->c_type) {
            case COL_INT:
                if(col->c_notnull == 0 && *(int*)value == INT_NULL)
                    printf("%7s", " ");
                else
                    printf("%7d ", *(int*)value);
                break;
            case COL_DOUBLE:
                if(col->c_notnull == 0 && *(double*)value == DOUBLE_NULL)
                    printf("%11s", " ");
                else
                    printf("%8.2lf ", *(double*)value);
                break;
            case COL_CHAR:
                printf("%10s ", value);
                break;
            }
        }
        printf("\n");
    }
}