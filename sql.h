#ifndef __SELECT_H
#define __SELECT_H

#include <glib.h>

#include "table.h"
#include "rnode.h"

/* ======================== conditon ======================= */

#define EXP_MAX 1024

#define COND_EQU 1
#define COND_ABOVE 2
#define COND_ABOVE_EQU 3
#define COND_BELOW 4
#define COND_BELOW_EQU 5
#define COND_NOT_EQU 6
#define COND_IS_NULL 7
#define COND_NOT_NULL 8

#define CHAR_COND_NOT '~'
#define CHAR_COND_AND '*'
#define CHAR_COND_OR '+'
#define CHAR_COND_TRUE '1'
#define CHAR_COND_FALSE '0'

struct condition {
    int type;
    char exp1[EXP_MAX];
    char exp2[EXP_MAX];
    GPtrArray * colref;
};

struct cond_set {
    GPtrArray * conds;
    char formula[EXP_MAX];
    int formula_len;
};

struct condition * condition_new_instance(int type, char * exp1, char * exp2);
void myg_condition_destroy(void * cond);


double compute_expression(char * exp);
int strreplace(char * str, const char * source, const char * dest, int max);

/* ======================= row_struct and dataset =============== */

struct row_struct {
    char ** data;
    //保存一份rnode的副本，用于UPDATE、DELETE
    struct rnode_m rnode;
};

#define DATASET_ERROR 1
#define DATASET_INFO 2

struct dataset {
    GPtrArray * column_set;
    GPtrArray * row_set;
    int row_size;
    int result;
    char info[1024];
};


void table_set_add_table(GPtrArray * tableset, struct table * tb);
void table_set_add_table_by_name(GPtrArray * tableset, struct database * db, char * tbname);
struct table * table_set_get_table(GPtrArray * tableset, int tbidx);
struct table * table_set_get_table_by_name(GPtrArray * tableset, char * tbname);
struct column * table_set_get_column(GPtrArray * tableset, char * colname);
void column_set_add_column(GPtrArray * colset, struct column * col);
struct column * column_set_add_column_by_name(GPtrArray * colset, GPtrArray * tbset,
        char * tbname, char * colname);


struct column * column_set_get_column(GPtrArray * colset, int colidx);
int column_set_get_column_id(GPtrArray * colset, struct column * col);
struct column * column_set_get_column_by_name(GPtrArray * colset, char * tbname, char * colname);



static struct row_struct * row_struct_new_instance(struct dataset * ds);
void * row_struct_get_value_by_id(struct row_struct * row, int colid);
void * row_struct_get_value(struct row_struct * row, GPtrArray * colset,
                            struct column * col);
void row_struct_set_single_value_by_id(struct row_struct * row, GPtrArray * colset,
                                       int colid, void * value);
int row_struct_set_single_value(struct row_struct * row, GPtrArray * colset,
                                struct column * col, void * value);
void row_struct_set_all_value(struct row_struct * row, GPtrArray * colset, ...);



struct dataset * dataset_new_instance();
void dataset_destroy(struct dataset * ds);

void dataset_add_column(struct dataset * ds, struct column * col);
void dataset_add_column_set(struct dataset * ds, GPtrArray * colset);
struct row_struct * dataset_add_row(struct dataset * ds);
struct row_struct * dataset_get_row(struct dataset * ds, int rowid);

struct dataset * dataset_traverse_table(struct table * tb, int copy_rnode, int colnr, ...);
struct dataset * dataset_join(struct dataset * ds1, struct dataset * ds2);
struct dataset * dataset_judge_condition(struct dataset * ds, struct cond_set * condset, int copy_rnode);
struct dataset * dataset_projection(struct dataset * ds, GPtrArray * colset);
void dataset_print(struct dataset * ds);



/* ======================== select info ======================= */

struct select_info {
    GPtrArray * tables;
    GPtrArray * columns;
    struct cond_set cond;
    struct column * orderby;
};

struct select_info * select_info_new_instance();
void select_info_destroy(struct select_info * si);
struct dataset * select_info_run(struct select_info * si);

struct expression * expression_new_instance(char * expstr);

/* ========================= upadate info ======================= */

struct expression {
    char expstr[EXP_MAX];
    GPtrArray * colref;
};

struct update_info {
    GPtrArray * table;
    GPtrArray * columns;
    GPtrArray * exps;
    struct cond_set cond;
    char info[EXP_MAX];		//UPDATE需要在执行时检查约束，如果出错输出信息
};

struct update_info * update_info_new_instance();
void update_info_destroy(struct update_info * ui);
int update_info_run(struct update_info * ui);

/* ========================= delete info ======================== */

struct delete_info {
    GPtrArray * table;
    struct cond_set cond;
};

struct delete_info * delete_info_new_instance();
void delete_info_destroy(struct delete_info * di);
int delete_info_run(struct delete_info * di);

/* ========================= insert info ======================== */

struct insert_info {
    GPtrArray * table;
    GPtrArray * values;
};

struct insert_info * insert_info_new_instance();
void insert_info_destroy(struct insert_info * ii);
int insert_info_run(struct insert_info * ii);

/* ====================== sql interface ==================== */

#define SQL_SELECT 1
#define SQL_INSERT 2
#define SQL_DELETE 3
#define SQL_UPDATE 4
#define SQL_CREATE_DB 5
#define SQL_USE_DB 6
#define SQL_DROP_DB 7
#define SQL_CREATE_TB 8

/* 除特殊情况，其他GPtrArray存放的都是char*指针 */
struct sql_info {
    int type;
    GPtrArray * cur_col_set;
    GPtrArray * column_set;

    GPtrArray * table_set;
    GPtrArray * database_set;
    GPtrArray * value_set;

    GPtrArray * cond_refcol_set[EXP_MAX];
    /* 存放的是struct condition *指针 */
    GPtrArray * condition_set;
    char cond_formula[EXP_MAX];

    //UPDATE语句SET后的表达式
    GPtrArray * exp_refcol_set[EXP_MAX];
    /* 存放的是struct expression *指针 */
    GPtrArray * expression_set;

    //CREATE TABLE语句列的定义
    GPtrArray * cur_col_def;
    GPtrArray * col_data_def;
    GPtrArray * col_def_set[EXP_MAX];


    char info[EXP_MAX];
    int info_offset;
};

struct dataset * run_sql(char * sql, ...);

extern struct sql_info * cur_sql;

void myg_char_strdup_destroy(void * str);

//该函数执行一条SELECT语句，可用于查询外键约束或唯一约束
int check_record_count(struct column * col, char * dbname, char * tbname, char * value);

#endif