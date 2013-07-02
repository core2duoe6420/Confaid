#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <glib.h>

#include "sql.h"


void myg_expression_destroy(void * exp)
{
    struct expression * expptr;
    expptr = (struct expression *)exp;
    if(expptr) {
        g_ptr_array_free(expptr->colref, FALSE);
        g_free(expptr);
    }
}

struct expression * expression_new_instance(char * expstr) {
    struct expression * exp;
    exp = (struct expression *)g_malloc0(sizeof(struct expression));
    assert(exp);

    strcpy(exp->expstr, expstr);
    exp->colref = g_ptr_array_sized_new(2);
    return exp;
}

double expression_transform(struct expression * exp, struct record * rec)
{
    char tmpexp[EXP_MAX] = {0, };
    strcpy(tmpexp, exp->expstr);
    for(int i = 0; i < exp->colref->len; i++) {
        struct column * col;
        char valuestr[EXP_MAX];
        col = column_set_get_column(exp->colref, i);
        void * value_in_rec;
        value_in_rec = record_column_get_value_by_name(rec, col->c_name);

        assert(col->c_type != COL_CHAR);

        switch(col->c_type) {
        case COL_DOUBLE:
            sprintf(valuestr, "%lf", *(double*)value_in_rec);
            break;
        case COL_INT:
            sprintf(valuestr, "%d", *(int*)value_in_rec);
            break;
        }

        strreplace(tmpexp, col->c_name, valuestr, sizeof(tmpexp));
    }

    return compute_expression(tmpexp);
}

struct update_info * update_info_new_instance() {
    struct update_info * ui;
    ui = (struct update_info *)g_malloc0(sizeof(struct update_info));
    assert(ui);

    ui->columns = g_ptr_array_sized_new(8);
    ui->table = g_ptr_array_new();
    ui->exps = g_ptr_array_sized_new(8);
    g_ptr_array_set_free_func(ui->exps, myg_expression_destroy);

    ui->cond.conds = g_ptr_array_sized_new(8);
    g_ptr_array_set_free_func(ui->cond.conds, myg_condition_destroy);

    return ui;
}

void update_info_destroy(struct update_info * ui)
{
    g_ptr_array_free(ui->columns, FALSE);
    g_ptr_array_free(ui->exps, TRUE);
    g_ptr_array_free(ui->table, TRUE);
    g_ptr_array_free(ui->cond.conds, TRUE);
}

int update_info_run(struct update_info * ui)
{
    struct dataset * ds;
    struct table * tb;
    tb = (struct table *)g_ptr_array_index(ui->table, 0);
    assert(tb);

    ds = dataset_traverse_table(tb, 1, tb->tb_col_nr);

    ds = dataset_judge_condition(ds, &ui->cond, 1);

    struct record * rec;
    rec = record_new_instance(tb);
    for(int rowid = 0; rowid < ds->row_set->len; rowid++) {
        struct row_struct * row;
        row = (struct row_struct *)g_ptr_array_index(ds->row_set, rowid);
        record_bind_rnode(rec, &row->rnode);
        record_read_buffer(rec);

        for(int expid = 0; expid < ui->columns->len; expid++) {
            struct column * col;
            struct expression * exp;
            col = column_set_get_column(ui->columns, expid);

            exp = (struct expression *)g_ptr_array_index(ui->exps, expid);
            //NULL值，约束在sql_info_to_update_info中已经检查完毕
            if(exp == NULL) {
                record_column_set_value_by_name(rec, col->c_name, NULL);
                continue;
            }
            //非NULL值，计算表达式
            void * value_addr;
            int ivalue;
            double dvalue;
            char valuestr[EXP_MAX];		//用于检查FK约束

            switch(col->c_type) {
                //CHAR直接引用字符串
            case COL_CHAR:
                value_addr = exp->expstr;
                strcpy(valuestr, exp->expstr);
                break;
            case COL_INT:
                ivalue = (int)expression_transform(exp, rec);
                sprintf(valuestr, "%d", ivalue);
                value_addr = &ivalue;
                break;
            case COL_DOUBLE:
                dvalue = expression_transform(exp, rec);
                sprintf(valuestr, "%lf", dvalue);
                value_addr = &dvalue;
                break;
            }
            //检查外键约束
            if(strcmp(col->c_fk_colname, "") != 0 &&
               strcmp(col->c_fk_colname, CHAR_NULL) != 0) {
                struct column * fkcol;
                struct table * fktb;
                fktb = table_get_by_name(tb->tb_db, col->c_fk_tbname);
                fkcol = table_get_column(fktb, col->c_fk_colname);
                assert(fkcol);
                int count;
                count = check_record_count(fkcol, tb->tb_db->d_header.dh_name,
                                           fktb->tb_name, valuestr);
                if(count == 0) {
                    sprintf(ui->info, "SQL: constraint violation %s FOREIGN KEY %s.%s",
                            col->c_name, col->c_fk_tbname, col->c_fk_colname);
                    dataset_destroy(ds);
                    record_destroy(rec);
                    return -1;
                }
            }
            //检查完毕
            record_column_set_value_by_name(rec, col->c_name, value_addr);
        }
        //写入新数据
        record_write_buffer(rec);
    }
    int count = ds->row_set->len;
    record_destroy(rec);
    dataset_destroy(ds);
    return count;
}