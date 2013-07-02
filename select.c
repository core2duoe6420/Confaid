#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "sql.h"

struct select_info * select_info_new_instance() {
    struct select_info * si;
    si = (struct select_info *)g_malloc0(sizeof(struct select_info));
    assert(si);

    si->columns = g_ptr_array_sized_new(16);
    si->tables = g_ptr_array_sized_new(8);

    si->cond.conds = g_ptr_array_sized_new(8);
    g_ptr_array_set_free_func(si->cond.conds, myg_condition_destroy);
    return si;
}

void select_info_destroy(struct select_info * si)
{
    g_ptr_array_free(si->columns, FALSE);
    g_ptr_array_free(si->tables, FALSE);
    g_ptr_array_free(si->cond.conds, TRUE);
    g_free(si);
}

struct dataset * select_info_run(struct select_info * si) {
    struct dataset * ds, * tmp;
    struct table * tb;
    tb = (struct table *)g_ptr_array_index(si->tables, 0);
    assert(tb);

    ds = dataset_traverse_table(tb, 0, tb->tb_col_nr);
    for(int i = 1; i < si->tables->len; i++) {
        struct table * tmptb;
        tmptb = (struct table *)g_ptr_array_index(si->tables, i);
        tmp = dataset_traverse_table(tmptb, 0, tmptb->tb_col_nr);
        //原来的ds和tmp应该都会被销毁
        ds = dataset_join(ds, tmp);
    }

    //现在ds是所有表的笛卡尔积
    if(si->cond.conds->len > 0)
        ds = dataset_judge_condition(ds, &si->cond, 0);

    //选择完成，投影
    ds = dataset_projection(ds, si->columns);
    return ds;
}