#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <assert.h>

#include "sql.h"

void myg_value_destroy(void * value)
{
    if(value)
        //values中的值应该是strdup生成的
        free(value);
}

struct insert_info * insert_info_new_instance() {
    struct insert_info * ii;
    ii = (struct insert_info *)g_malloc0(sizeof(struct insert_info));
    ii->table = g_ptr_array_new();
    ii->values = g_ptr_array_new();

    g_ptr_array_set_free_func(ii->values, myg_value_destroy);

    return ii;
}

void insert_info_destroy(struct insert_info * ii)
{
    g_ptr_array_free(ii->table, FALSE);
    g_ptr_array_free(ii->values, TRUE);
    g_free(ii);
}

static int value_is_null(struct column * col, char * value)
{
    static int initialized = 0;
    static char char_null_str[EXP_MAX];
    static char int_null_str[EXP_MAX];
    static char double_null_str[EXP_MAX];

    if(initialized == 0) {
        initialized = 1;
        sprintf(char_null_str, "%s", CHAR_NULL);
        sprintf(int_null_str, "%d", INT_NULL);
        sprintf(double_null_str, "%lf", DOUBLE_NULL);
    }

    int ret;
    switch(col->c_type) {
    case COL_CHAR:
        ret = strcmp(value, char_null_str);
        break;
    case COL_INT:
        ret = strcmp(value, int_null_str);
        break;
    case COL_DOUBLE:
        ret = strcmp(value, double_null_str);
        break;
    }

    return ret == 0;
}

/* 我们假定这里给出的ii已经验证过NOT NULL和类型
 */
int insert_info_run(struct insert_info * ii)
{
    struct table * tb;
    struct block * b;
    tb = (struct table *)g_ptr_array_index(ii->table, 0);
    assert(tb);

    b = table_get_block(tb);
    //block的片接近用完？
    while(b && b->bitmap.usable < tb->tb_record_size / b->header.piece_size + 2)
        b = b->tb_prev;

    assert(b);

    struct record * rec;
    rec = record_new_instance(tb);

    for(int i = 0; i < tb->tb_col_nr; i++) {
        struct column * col;
        char * value;
        void * addr = NULL;
        int ivalue;
        double dvalue;
        col = &tb->tb_cols[i];
        //value是NULL说明该值为NULL
        value = (char *)g_ptr_array_index(ii->values, i);
        if(value) {
            switch(col->c_type) {
            case COL_INT:
                ivalue = atoi(value);
                addr = &ivalue;
                break;
            case COL_DOUBLE:
                dvalue = atof(value);
                addr = &dvalue;
                break;
            case COL_CHAR:
                addr = value;
                break;
            }
        }
        record_column_set_value(rec, i, addr);
    }

    struct rnode_m * rn;
    rn = rnode_get_usable(b);
    if(rn == NULL) {
        record_destroy(rec);
        return 1;
    }
    record_bind_rnode(rec, rn);
    if(record_alloc_piece(rec) == 0) {
        rnode_destroy(rn);
        record_destroy(rec);
        return 1;
    }
    record_write_buffer(rec);

    rnode_destroy(rn);
    record_destroy(rec);

    return 0;
}