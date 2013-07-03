#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sql.h"

struct condition * condition_new_instance(int type, char * exp1, char * exp2) {
    struct condition * cond;
    cond = (struct condition *)g_malloc0(sizeof(struct condition));
    assert(cond);

    strcpy(cond->exp1, exp1);
    strcpy(cond->exp2, exp2);

    cond->type = type;

    cond->colref = g_ptr_array_sized_new(2);
    return cond;
}

void myg_condition_destroy(void * cond)
{
    struct condition * tmpcond;
    tmpcond = (struct condition *)cond;
    g_ptr_array_free(tmpcond->colref, FALSE);
    g_free(cond);
}

//返回替换的次数
int strreplace(char * str, const char * source, const char * dest, int max)
{
    int count = 0;
    char * tmp;
    tmp = (char *)g_malloc(max);
    assert(tmp);

    int destlen = strlen(dest);
    int srclen = strlen(source);
    strcpy(tmp, str);

    char * idxptr, * lastptr = tmp;
    int distance = 0, offset = 0;
    while((idxptr = strstr(lastptr, source))) {
        count++;
        //distance是当str中找到多个source时，两个source之间的字符数量
        distance = idxptr - lastptr;
        //将两个source之间的字符串复制到str
        if(offset + distance >= max) {
            count = -1;
            break;
        }
        memcpy(str + offset, lastptr, distance);
        offset += distance;
        //将dest复制到str
        if(offset + destlen >= max) {
            count = -1;
            break;
        }
        memcpy(str + offset, dest, destlen);
        offset += destlen;

        lastptr = idxptr + srclen;
    }
    //余下的字符
    if(offset + strlen(lastptr) > max)
        count = -1;
    else
        strcpy(str + offset, lastptr);

    g_free(tmp);
    return count;
}

int condition_judge(struct condition * cond, struct row_struct * row, GPtrArray * colset)
{
    int col_set_idx;
    char tmp1[EXP_MAX], tmp2[EXP_MAX];
    char valuestr[EXP_MAX], tablename[EXP_MAX];
    strcpy(tmp1, cond->exp1);
    strcpy(tmp2, cond->exp2);

    //not null或者is null单独处理
    struct column * ref;
    void * value;
    if(cond->type == COND_NOT_NULL || cond->type == COND_IS_NULL) {
        int isnull = 0;
        ref = column_set_get_column(cond->colref, 0);
        value = row_struct_get_value(row, colset, ref);
        switch(ref->c_type) {
        case COL_CHAR:
            if(ref->c_notnull == 0 && strcmp((char*)value, CHAR_NULL) == 0)
                isnull = 1;
            break;
        case COL_INT:
            if(ref->c_notnull == 0 && *(int*)value == INT_NULL)
                isnull = 1;
            break;
        case COL_DOUBLE:
            if(ref->c_notnull == 0 && *(double*)value == DOUBLE_NULL)
                isnull = 1;
            break;
        }
        if(isnull == 1)
            return cond->type == COND_IS_NULL;
        else
            return cond->type == COND_NOT_NULL;
    }

    //正常情况
    int type;
    for(int i = 0; i < cond->colref->len; i++) {
        ref = column_set_get_column(cond->colref, i);
        value = row_struct_get_value(row, colset, ref);
        type = ref->c_type;
        switch(ref->c_type) {
        case COL_CHAR:
            sprintf(valuestr, "%s", value);
            break;
        case COL_INT:
            sprintf(valuestr, "%d", *(int*)value);
            break;
        case COL_DOUBLE:
            sprintf(valuestr, "%lf", *(double*)value);
            break;
        }

        sprintf(tablename, "%s.%s", ref->c_tbname, ref->c_name);
        strreplace(tmp1, tablename, valuestr, EXP_MAX);
        strreplace(tmp2, tablename, valuestr, EXP_MAX);
        sprintf(tablename, "%s", ref->c_name);
        char * pos;
        if((pos = strstr(tmp1, tablename)) && *(pos - 1) != '.')
            strreplace(tmp1, tablename, valuestr, EXP_MAX);
        if((pos = strstr(tmp2, tablename)) && *(pos - 1) != '.')
            strreplace(tmp2, tablename, valuestr, EXP_MAX);
    }

    int result = 0;
    if(type != COL_CHAR) {
        double expvalue1, expvalue2;
        expvalue1 = compute_expression(tmp1);
        assert(expvalue1 != DBL_MIN);
        expvalue2 = compute_expression(tmp2);
        assert(expvalue2 != DBL_MIN);

        result = expvalue1 - expvalue2;
    } else {
        result = strcmp(tmp1, tmp2);
    }

    if(result > 0)
        return cond->type == COND_ABOVE ||
               cond->type == COND_ABOVE_EQU ||
               cond->type == COND_NOT_EQU;
    else if(result < 0)
        return cond->type == COND_BELOW ||
               cond->type == COND_BELOW_EQU ||
               cond->type == COND_NOT_EQU;
    else if(result == 0)
        return cond->type == COND_EQU ||
               cond->type == COND_ABOVE_EQU ||
               cond->type == COND_BELOW_EQU;
}

int cond_set_judge(struct cond_set * condset, struct row_struct * row, GPtrArray * colset)
{
    char tmp[EXP_MAX];
    strcpy(tmp, condset->formula);
    for(int i = 0; i < condset->conds->len; i++) {
        int condret;
        struct condition * cond;
        cond = (struct condition *)g_ptr_array_index(condset->conds, i);
        condret = condition_judge(cond, row, colset);

        for(int j = 0; j < condset->formula_len; j++) {
            if(tmp[j] == 'c') {
                tmp[j] = (condret == 0 ? '0' : '1');
                break;
            }
        }
    }
    double condset_result;
    condset_result = compute_expression(tmp);
    assert(condset_result != DBL_MIN);

    return condset_result == 0. ? 0 : 1;
}

struct dataset * dataset_judge_condition(struct dataset * ds, struct cond_set * condset, int copy_rnode) {
    //没有条件直接返回
    if(condset->conds->len == 0)
        return ds;

    struct dataset * newds;
    newds = dataset_new_instance();

    dataset_add_column_set(newds, ds->column_set);

    for(int i = 0; i < ds->row_set->len; i++) {
        struct row_struct * row;
        row = (struct row_struct *)g_ptr_array_index(ds->row_set, i);

        int boolean;
        boolean = cond_set_judge(condset, row, ds->column_set);
        if(boolean) {
            struct row_struct * newrow;
            newrow = dataset_add_row(newds);
            void * newrow_data_address = newrow->data[0];
            void * dsrow_data_address = row->data[0];
            memcpy(newrow_data_address, dsrow_data_address, ds->row_size);
            if(copy_rnode)
                memcpy(&newrow->rnode, &row->rnode, sizeof(struct rnode_m));
        }
    }

    //注意！会销毁ds！！！
    dataset_destroy(ds);
    return newds;
}