#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "sql.h"

#define TEMP_SQL_FILE "temp.sql"
#define TEMP_RESULT_FILE "result.tmp"

extern int yyparse();
extern FILE * yyin, * yyout;
void un_sql();
void start_sql();

struct sql_info * cur_sql = NULL;


void myg_char_strdup_destroy(void * str)
{
    //strdup����malloc��������g_free
    free(str);
}

struct sql_info * sql_info_new_instance() {
    struct sql_info * sql;
    sql = (struct sql_info *)g_malloc0(sizeof(struct sql_info));
    assert(sql);

    //condition_set�е�condition���ջᱻ���õ������ṹ��condition��
    //���Բ���Ҫfree
    sql->condition_set = g_ptr_array_sized_new(8);

    //cur_col_set�����л�column_set��cond_refcol
    sql->cur_col_set = g_ptr_array_sized_new(8);
    g_ptr_array_set_free_func(sql->cur_col_set, myg_char_strdup_destroy);

    sql->database_set = g_ptr_array_new();
    g_ptr_array_set_free_func(sql->database_set, myg_char_strdup_destroy);

    sql->table_set = g_ptr_array_sized_new(4);
    g_ptr_array_set_free_func(sql->table_set, myg_char_strdup_destroy);

    sql->value_set = g_ptr_array_sized_new(8);
    g_ptr_array_set_free_func(sql->value_set, myg_char_strdup_destroy);

    //��conditionͬ��expressionָ��ᱻ���õ�����ptrarray�У�����Ҫ�ͷ�
    sql->expression_set = g_ptr_array_sized_new(2);

    return sql;
}

void sql_info_destroy(struct sql_info * sql)
{
    if(sql->cur_col_set)
        g_ptr_array_free(sql->cur_col_set, TRUE);
    if(sql->column_set)
        g_ptr_array_free(sql->column_set, TRUE);

    for(int i = 0; i < sql->condition_set->len; i++)
        if(sql->cond_refcol_set[i])
            g_ptr_array_free(sql->cond_refcol_set[i], TRUE);

    for(int i = 0; i < sql->expression_set->len; i++)
        if(sql->exp_refcol_set[i])
            g_ptr_array_free(sql->exp_refcol_set[i], TRUE);

    if(sql->database_set)
        g_ptr_array_free(sql->database_set, TRUE);
    if(sql->table_set)
        g_ptr_array_free(sql->table_set, TRUE);
    if(sql->value_set)
        g_ptr_array_free(sql->value_set, TRUE);
    if(sql->condition_set)
        g_ptr_array_free(sql->condition_set, FALSE);
    if(sql->expression_set)
        g_ptr_array_free(sql->expression_set, FALSE);
    g_free(sql);
}

//��NAME.NAME�ĸ�ʽ�ֽ⵽prefix��name������tablename.colname����dbname.tbname
void static resolve_name(char * source, char * prefix, char * name)
{
    char * pos = NULL;
    //������
    if((pos = strchr(source, '.')) == NULL) {
        strcpy(name, source);
        prefix[0] = 0;
        return;
    }

    *pos = 0;
    strcpy(prefix, source);
    strcpy(name, pos + 1);
    *pos = '.';
    return;
}


struct database * get_database(char * dbname) {
    if(dbname == NULL || dbname[0] == 0)
        return cur_db;

    struct database * db = db_set;
    while(db && strcmp(db->d_header.dh_name, dbname) != 0)
        db = db->d_next_db;
    return db;
}

struct table * get_table(struct database * db, char * tbname) {
    if(db == NULL)
        db = get_database(NULL);

    if(db == NULL)
        return NULL;

    return table_get_by_name(db, tbname);
}

struct column * get_column(struct table * tb, char * colname) {
    for(int i = 0; i < tb->tb_col_nr; i++)
        if(strcmp(tb->tb_cols[i].c_name, colname) == 0)
            return &tb->tb_cols[i];

    return NULL;
}

int check_record_count(struct column * col, char * dbname, char * tbname, char * value)
{
    char sqlstr[1024];
    switch(col->c_type) {
    case COL_CHAR:
        sprintf(sqlstr, "SELECT * FROM %s.%s WHERE %s=='%s';", dbname, tbname, col->c_name, value);
        break;
    case COL_INT:
        sprintf(sqlstr, "SELECT * FROM %s.%s WHERE %s==%d;", dbname, tbname, col->c_name, atoi(value));
        break;
    case COL_DOUBLE:
        sprintf(sqlstr, "SELECT * FROM %s.%s WHERE %s==%lf;", dbname, tbname, col->c_name, atof(value));
        break;
    }
    struct dataset * result;
    result = run_sql(sqlstr);
    int count;
    count = result->row_set->len;
    dataset_destroy(result);

    return count;
}

//����UPDATE����м��CHAR���͵��еı��ʽ�Ƿ��������
int check_string_operator(char * exp)
{
    while(*exp) {
        if(*exp == '+' || *exp == '-' ||
           *exp == '*' || *exp == '/' ||
           *exp == '(' || *exp == ')')
            return 1;
        exp++;
    }
    return 0;
}

/* �ú�������sql_info_to_xת������ʹ�ã����ڼ��table�Ƿ����
 * �������÷�Ϊ���֣�һ��ΪNAME��һ��ΪDBNAME.NAME���ú�������Ӧǰ��
 * ���޸�db��ָ���ֵ�������������sql->error_infoд�������Ϣ
 */
static struct table * check_table_name(GPtrArray * tbname_set, int idx_in_set,
                                       struct database ** db, struct sql_info * sql) {
    char * value_in_set;
    struct table * tb;
    char prefix[EXP_MAX], name[EXP_MAX];
    value_in_set = (char *)g_ptr_array_index(tbname_set, idx_in_set);
    resolve_name(value_in_set, prefix, name);
    *db = get_database(prefix);
    tb = get_table(*db, name);
    if(tb == NULL)
        sprintf(sql->info, "SQL: table %s not exists", value_in_set);

    return tb;
}

/* �ú�������sql_info_to_xת������ʹ�ã�����ת�������ṹ��������������õ����Ƿ����
 * �ú�����Ҫһ��table_set��Ӧ�����������������ڱ������
 * ����������sql->error_infoд�������Ϣ
 * �ɹ�����0��������1
 */
static int check_and_transform_condition(struct sql_info * sql, GPtrArray * tbset, struct cond_set * condset)
{
    for(int i = 0; i < sql->condition_set->len; i++) {
        struct condition * cond;
        GPtrArray * colref;
        struct column * col;
        char prefix[EXP_MAX], name[EXP_MAX];
        char * value_in_set;
        cond = (struct condition *)g_ptr_array_index(sql->condition_set, i);
        colref = sql->cond_refcol_set[i];
        for(int j = 0; j < colref->len; j++) {
            value_in_set = (char *)g_ptr_array_index(colref, j);
            resolve_name(value_in_set, prefix, name);
            col = column_set_add_column_by_name(cond->colref, tbset, prefix, name);
            if(col == NULL) {
                sprintf(sql->info, "SQL: column %s not exists", value_in_set);
                return 1;
            }
        }
        g_ptr_array_add(condset->conds, cond);
    }

    strcpy(condset->formula, sql->cond_formula);
    condset->formula_len = strlen(condset->formula);
    return 0;
}

/* �ú�������sql_info_to_xת������ʹ�ã����ڼ��column�Ƿ������tbָ��ı���
 * �������÷�Ϊ���֣�һ��ΪNAME��һ��ΪTBNAME.NAME���ú�������Ӧǰ��
 * �����������sql->error_infoд�������Ϣ
 */
static struct column * check_column_name(GPtrArray * colname_set, int idx_in_set,
        struct table * tb, struct sql_info * sql) {
    struct column * col;
    char * colname = (char*)g_ptr_array_index(colname_set, idx_in_set);
    col = get_column(tb, colname);
    if(col == NULL)
        sprintf(sql->info, "SQL: column %s not exists", colname);

    return col;
}

struct update_info * sql_info_to_update_info(struct sql_info * sql) {
    //���ʽ����������һ��
    assert(sql->column_set->len == sql->expression_set->len);

    struct update_info * ui;
    ui = update_info_new_instance();

    struct database * db;
    struct table * tb;

    //������
    tb = check_table_name(sql->table_set, 0, &db, sql);
    if(tb == NULL) {
        update_info_destroy(ui);
        return NULL;
    }
    table_set_add_table(ui->table, tb);

    //���column�ͱ��ʽ
    for(int i = 0; i < sql->column_set->len; i++) {
        struct column * col;
        col = check_column_name(sql->column_set, i, tb, sql);
        if(col == NULL) {
            update_info_destroy(ui);
            return NULL;
        }
        column_set_add_column(ui->columns, col);

        //�����ʽ�������Ƿ���ڣ�������ֵ���������Ƿ���ͬ
        struct expression * exp;
        GPtrArray * exp_ref_colset;
        struct column * refcol;

        exp = (struct expression *)g_ptr_array_index(sql->expression_set, i);
        exp_ref_colset = sql->exp_refcol_set[i];

        //NULLֵ��Ҫ���Լ��
        if(exp == NULL) {
            assert(exp_ref_colset == NULL);
            if(col->c_notnull == 1) {
                sprintf(sql->info, "SQL: constraint violation %s NOT NULL", col->c_name);
                update_info_destroy(ui);
                return NULL;
            }
            g_ptr_array_add(ui->exps, NULL);
            continue;
        }

        //CHAR�������Ӽ��˳�������
        if(col->c_type == COL_CHAR && check_string_operator(exp->expstr)) {
            sprintf(sql->info, "SQL: operation between CHAR type column %s", col->c_name);
            update_info_destroy(ui);
            return NULL;
        }

        for(int refcol_idx = 0; refcol_idx < exp_ref_colset->len; refcol_idx++) {
            refcol = check_column_name(exp_ref_colset, refcol_idx, tb, sql);
            if(col == NULL) {
                update_info_destroy(ui);
                return NULL;
            }
            //�������
            if(refcol->c_type != col->c_type) {
                sprintf(sql->info, "SQL: expression between inconsistent type %s %s",
                        col->c_name, refcol->c_name);
                update_info_destroy(ui);
                return NULL;
            }
            column_set_add_column(exp->colref, refcol);
        }

        //�����ϣ�������ʽ
        g_ptr_array_add(ui->exps, exp);
    }

    //����
    if(check_and_transform_condition(sql, ui->table, &ui->cond)) {
        update_info_destroy(ui);
        return NULL;
    }

    return ui;
}

struct insert_info * sql_info_to_insert_info(struct sql_info * sql) {
    //�����Ͳ�����������һ��
    if(sql->column_set->len != 0 &&
       sql->column_set->len != sql->value_set->len) {
        sprintf(sql->info, "SQL: inconsistent number of column and value");
        return NULL;
    }

    struct insert_info * ii;
    ii = insert_info_new_instance();

    struct database * db;
    struct table * tb;
    char * value_in_set;
    char prefix[EXP_MAX], name[EXP_MAX];
    assert(sql->table_set->len == 1);

    //���table
    tb = check_table_name(sql->table_set, 0, &db, sql);
    if(tb == NULL) {
        insert_info_destroy(ii);
        return NULL;
    }
    table_set_add_table(ii->table, tb);

    //���column��insert_info����Ҫcolumn��Ϣ����������鱣֤�������ļ����ȷ��
    //INSERT���û��ָ������ʱlenΪ0��������for���
    for(int i = 0; i < sql->column_set->len; i++) {
        struct column * col;
        col = check_column_name(sql->column_set, i, tb, sql);
        if(col == NULL) {
            insert_info_destroy(ii);
            return NULL;
        }
    }

    //���ڱ��е�ÿһ�У�������value_set�е�ֵ��û��������Ϊ��Ӧ��NULLֵ
    for(int i = 0; i < tb->tb_col_nr; i++) {
        struct column * col;
        int valueidx = -1;

        col = &tb->tb_cols[i];
        if(sql->column_set->len == 0) {
            valueidx = i;
        } else {
            for(int j = 0; j < sql->column_set->len; j++) {
                char * colname;
                colname = (char *)g_ptr_array_index(sql->column_set, j);
                if(strcmp(colname, col->c_name) == 0) {
                    valueidx = j;
                    break;
                }
            }
        }
        char * value = NULL;
        if(valueidx >= 0)
            value = (char *)g_ptr_array_index(sql->value_set, valueidx);
        //�Ƿ�Υ��NOT NULLԼ����
        if(col->c_notnull != 0 && value == NULL) {
            sprintf(sql->info, "SQL: constraint violation %s NOT NULL", col->c_name);
            insert_info_destroy(ii);
            return NULL;
        }
        //�Ƿ�Υ��UNIQUEԼ����
        if(value && col->c_unique != 0) {
            char * dbname = tb->tb_db->d_header.dh_name;
            int count = check_record_count(col, dbname, tb->tb_name, value);
            if(count != 0) {
                sprintf(sql->info, "SQL: constraint violation %s UNIQUE", col->c_name);
                insert_info_destroy(ii);
                return NULL;
            }
        }
        //�Ƿ�Υ�����Լ����
        if(value && strcmp(col->c_fk_colname, "") != 0 &&
           strcmp(col->c_fk_colname, CHAR_NULL) != 0) {
            char * dbname = tb->tb_db->d_header.dh_name;
            struct table * fktb = table_get_by_name(db, col->c_fk_tbname);
            struct column * fkcol = table_get_column(fktb, col->c_fk_colname);
            assert(fkcol);
            int count = check_record_count(fkcol, dbname, col->c_fk_tbname, value);
            if(count == 0) {
                sprintf(sql->info, "SQL: constraint violation %s FOREIGN KEY %s.%s",
                        col->c_name, col->c_fk_tbname, col->c_fk_colname);
                insert_info_destroy(ii);
                return NULL;
            }
        }

        //�����ϣ�����ֵ��ע�⣬��Щֵȫ��char*�����ΪΪ�գ�����NULLָ��
        if(value)
            g_ptr_array_add(ii->values, strdup(value));
        else
            g_ptr_array_add(ii->values, NULL);
    }
    return ii;
}

struct delete_info * sql_info_to_delete_info(struct sql_info * sql) {
    struct delete_info * di;
    di = delete_info_new_instance();

    struct database * db;
    struct table * tb;

    //������
    tb = check_table_name(sql->table_set, 0, &db, sql);
    if(tb == NULL) {
        delete_info_destroy(di);
        return NULL;
    }
    table_set_add_table(di->table, tb);

    //����
    if(check_and_transform_condition(sql, di->table, &di->cond)) {
        delete_info_destroy(di);
        return NULL;
    }

    return di;
}

struct select_info * sql_info_to_select_info(struct sql_info * sql) {
    struct select_info * si;
    si = select_info_new_instance();

    struct database * db;
    struct table * tb;
    struct column * col;
    char prefix[EXP_MAX], name[EXP_MAX];
    char * value_in_set;
    //������
    for(int i = 0; i < sql->table_set->len; i++) {
        tb = check_table_name(sql->table_set, i, &db, sql);
        if(tb == NULL) {
            select_info_destroy(si);
            return NULL;
        }
        table_set_add_table(si->tables, tb);
    }
    //������ ��Ϊ * ���б����� * �����б������е���ȫ���ӽ�ȥ
    if(sql->column_set->len == 1 &&
       strcmp((char*)g_ptr_array_index(sql->column_set, 0), "*") == 0) {
        for(int i = 0; i < si->tables->len; i++) {
            tb = (struct table *)g_ptr_array_index(si->tables, i);
            for(int j = 0; j < tb->tb_col_nr; j++) {
                col = &tb->tb_cols[j];
                g_ptr_array_add(si->columns, col);
            }
        }
    } else {
        for(int i = 0; i < sql->column_set->len; i++) {
            value_in_set = (char *)g_ptr_array_index(sql->column_set, i);
            resolve_name(value_in_set, prefix, name);
            col = column_set_add_column_by_name(si->columns, si->tables, prefix, name);
            if(col == NULL) {
                sprintf(sql->info, "SQL: column %s not exists", value_in_set);
                select_info_destroy(si);
                return NULL;
            }
        }
    }
    //����
    if(check_and_transform_condition(sql, si->tables, &si->cond)) {
        select_info_destroy(si);
        return NULL;
    }

    return si;
}

struct dataset * dataset_error(char * err) {
    struct dataset * ds;
    ds = dataset_new_instance();
    ds->result = DATASET_ERROR;
    strcpy(ds->info, err);
    return ds;
}

struct dataset * dataset_info(char * info, ...) {
    struct dataset * ds;
    char tmpinfo[EXP_MAX];
    va_list ap;
    va_start(ap, info);
    vsprintf(tmpinfo, info, ap);
    va_end(ap);

    ds = dataset_new_instance();
    ds->result = DATASET_INFO;
    strcpy(ds->info, tmpinfo);
    return ds;
}

struct dataset * sql_info_run(struct sql_info * sql) {
    void * structure;
    struct dataset * ds = NULL;
    int affected_row_count;
    switch(sql->type) {
    case SQL_SELECT:
        structure = sql_info_to_select_info(sql);
        if(structure == NULL) {
            ds = dataset_error(sql->info);
        } else {
            ds = select_info_run((struct select_info *)structure);
            select_info_destroy((struct select_info *)structure);
        }
        break;
    case SQL_INSERT:
        structure = sql_info_to_insert_info(sql);
        if(structure == NULL) {
            ds = dataset_error(sql->info);
        } else {
            affected_row_count = insert_info_run((struct insert_info *)structure);
            insert_info_destroy((struct insert_info *)structure);
            ds = dataset_info("%d row affected", affected_row_count);
        }
        break;
    case SQL_DELETE:
        structure = sql_info_to_delete_info(sql);
        if(structure == NULL) {
            ds = dataset_error(sql->info);
        } else {
            affected_row_count = delete_info_run((struct delete_info *)structure);
            delete_info_destroy((struct delete_info *)structure);
            ds = dataset_info("%d row affected", affected_row_count);
        }
        break;
    case SQL_UPDATE:
        structure = sql_info_to_update_info(sql);
        if(structure == NULL) {
            ds = dataset_error(sql->info);
        } else {
            affected_row_count = update_info_run((struct update_info *)structure);
            if(affected_row_count >= 0)
                ds = dataset_info("%d row affected", affected_row_count);
            else
                ds = dataset_error(((struct update_info *)structure)->info);
            update_info_destroy((struct update_info *)structure);

        }
        break;
    }
    return ds;
}

int analyze_sql(char * infile)
{
    //���������룡
    static int in_sql = 0;
    assert(in_sql == 0);

    in_sql = 1;
    un_sql();
    yyin = fopen(infile, "r");
    if(yyin == NULL)
        return 1;

    int ret;
    start_sql();
    ret = yyparse();
    fclose(yyin);
    un_sql();
    remove(infile);

    in_sql = 0;
    return ret;
}

static struct dataset * _run_sql(char * sql) {
    FILE * fp;
    fp = fopen(TEMP_SQL_FILE, "w");
    assert(fp);

    fprintf(fp, sql);
    fclose(fp);
    //lastsql����Ƕ�ײ�ѯ����ֵ������ջ��
    struct sql_info * lastsql;
    lastsql = cur_sql;
    cur_sql = sql_info_new_instance();

    int result;
    result = analyze_sql(TEMP_SQL_FILE);

    struct dataset * ds;

    if(result == 0)
        ds = sql_info_run(cur_sql);
    else
        ds = dataset_error(cur_sql->info);

    sql_info_destroy(cur_sql);
    cur_sql = lastsql;
    return ds;
}

struct dataset * run_sql(char * sql, ...) {
    char sqlstr[EXP_MAX];
    va_list ap;
    va_start(ap, sql);
    vsprintf(sqlstr, sql, ap);
    va_end(ap);
    return _run_sql(sqlstr);
}

#include "buffer.h"

void main()
{
    initial_buffer(1024 * 1024, 4096);
    initial_dictionary();
    cur_db = dic_db;
    //search_dic_database("dictionary");
    struct dataset * ds;
    ds = run_sql("UPDATE columns SET offset=colname;");
    if(ds)
        dataset_print(ds);
    ds = run_sql("SELECT tbname,colname,offset,prikey FROM columns;");
    if(ds)
        dataset_print(ds);
    buffer_flush();
}
