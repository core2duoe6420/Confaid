#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <glib.h>

#include "sql.h"
#include "rnode.h"


struct delete_info * delete_info_new_instance() {
    struct delete_info * di;
    di = (struct delete_info *)g_malloc0(sizeof(struct delete_info));
    assert(di);

    di->table = g_ptr_array_new();

    di->cond.conds = g_ptr_array_sized_new(8);
    g_ptr_array_set_free_func(di->cond.conds, myg_condition_destroy);

    return di;
}

void delete_info_destroy(struct delete_info * di)
{
    g_ptr_array_free(di->table, FALSE);
    g_ptr_array_free(di->cond.conds, TRUE);
    g_free(di);
}

int delete_info_run(struct delete_info * di)
{
    struct dataset * ds;
    struct table * tb;
    tb = table_set_get_table(di->table, 0);

    assert(tb);

    ds = dataset_traverse_table(tb, 1, tb->tb_col_nr);

    ds = dataset_judge_condition(ds, &di->cond, 1);

    int count = ds->row_set->len;

    for(int i = 0; i < count; i++) {
        struct row_struct * row;
        row = (struct row_struct *)g_ptr_array_index(ds->row_set, i);
        int piecenr;
        piecenr = rnode_remove(&row->rnode);
        assert(piecenr);
    }

    dataset_destroy(ds);

    return count;
}