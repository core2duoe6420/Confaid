#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//for access
#ifndef __LINUX__
#include <io.h>
#else
#include <unistd.h>
#endif

#include "database.h"
#include "table.h"
#include "sql.h" //for check_record_count

#define DIC_FILENAME "confaid.dic"
#define DIC_DBNAME "dictionary"
#define DIC_BLOCK_SIZE (2*1024*1024)

#define DIC_TABLE_DATABASE "databases"
#define DIC_TABLE_TABLES "tables"
#define DIC_TABLE_COLUMNS "columns"

#define __offset(field, structure) \
	((size_t)(&((struct structure *)0)->field))

struct dic_database {
    char dbname[NAMEMAX_LEN + 1];
    char filename[NAMEMAX_LEN + 1];
};

static struct column dic_database_cols[] = {
    {
        COL_CHAR, NAMEMAX_LEN + 1, 1, 1, "dbname", DIC_TABLE_DATABASE, DIC_DBNAME,
        __offset(dbname, dic_database), "", "", 1
    },
    {
        COL_CHAR, NAMEMAX_LEN + 1, 1, 0, "dbfile", DIC_TABLE_DATABASE, DIC_DBNAME,
        __offset(filename, dic_database), "", "", 1
    },
};

struct dic_table {
    char tbname[NAMEMAX_LEN + 1];
    char dbname[NAMEMAX_LEN + 1];
};

static struct column dic_table_cols[] = {
    {
        COL_CHAR, NAMEMAX_LEN + 1, 1, 1, "tbname", DIC_TABLE_TABLES, DIC_DBNAME,
        __offset(tbname, dic_table), "", "", 0
    },
    {
        COL_CHAR, NAMEMAX_LEN + 1, 1, 1, "dbname", DIC_TABLE_TABLES, DIC_DBNAME,
        __offset(dbname, dic_table), DIC_TABLE_DATABASE, "dbname", 0
    },
};

static struct column dic_column_cols[] = {
    {
        COL_INT, sizeof(int), 1, 0, "type", DIC_TABLE_COLUMNS, DIC_DBNAME,
        __offset(c_type, column), "", "", 0
    },
    {
        COL_INT, sizeof(int), 1, 0, "size", DIC_TABLE_COLUMNS, DIC_DBNAME,
        __offset(c_size, column), "", "", 0
    },
    {
        COL_INT, sizeof(int), 1, 0, "notnull", DIC_TABLE_COLUMNS, DIC_DBNAME,
        __offset(c_notnull, column), "", "", 0
    },
    {
        COL_INT, sizeof(int), 1, 0, "prikey", DIC_TABLE_COLUMNS, DIC_DBNAME,
        __offset(c_pri_key, column), "", "", 0
    },
    {
        COL_CHAR, NAMEMAX_LEN + 1, 1, 1, "colname", DIC_TABLE_COLUMNS, DIC_DBNAME,
        __offset(c_name, column), "", "", 0
    },
    {
        COL_CHAR, NAMEMAX_LEN + 1, 1, 1, "tbname", DIC_TABLE_COLUMNS, DIC_DBNAME,
        __offset(c_tbname, column), DIC_TABLE_TABLES, "tbname", 0
    },
    {
        COL_CHAR, NAMEMAX_LEN + 1, 1, 1, "dbname", DIC_TABLE_COLUMNS, DIC_DBNAME,
        __offset(c_dbname, column), DIC_TABLE_DATABASE, "dbname", 0
    },
    {
        COL_INT, sizeof(int), 1, 0, "offset", DIC_TABLE_COLUMNS, DIC_DBNAME,
        __offset(c_offset, column), "", "", 0
    },
    {
        COL_CHAR, NAMEMAX_LEN + 1, 0, 0, "fk_tbname", DIC_TABLE_COLUMNS, DIC_DBNAME,
        __offset(c_fk_tbname, column), DIC_TABLE_TABLES, "tbname", 0
    },
    {
        COL_CHAR, NAMEMAX_LEN + 1, 0, 0, "fk_colname", DIC_TABLE_COLUMNS, DIC_DBNAME,
        __offset(c_fk_colname, column), DIC_TABLE_COLUMNS, "colname", 0
    },
    {
        COL_INT, sizeof(int), 1, 0, "unique", DIC_TABLE_COLUMNS, DIC_DBNAME,
        __offset(c_unique, column), "", "", 0
    },
};

struct database * dic_db = NULL;

static void _dic_database_insert(struct table * tb, char * dbstr, char * filestr)
{
    char dbname[NAMEMAX_LEN + 1], fname[NAMEMAX_LEN + 1];
    strncpy(dbname, dbstr, sizeof(dbname));
    strncpy(fname, filestr, sizeof(fname));

    table_insert_record(tb, dbname, fname);
}

void dic_database_insert(char * dbstr, char * filestr)
{
    struct table * tb;
    tb = table_get_by_name(dic_db, DIC_TABLE_DATABASE);
    _dic_database_insert(tb, dbstr, filestr);
}

static void _dic_table_insert(struct table * tb, char * tbstr, char * dbstr)
{
    char tbname[NAMEMAX_LEN + 1], dbname[NAMEMAX_LEN + 1];
    strncpy(tbname, tbstr, sizeof(tbname));
    strncpy(dbname, dbstr, sizeof(dbname));

    table_insert_record(tb, tbname, dbname);
}

void dic_table_insert(char * dbstr, char * filestr)
{
    struct table * tb;
    tb = table_get_by_name(dic_db, DIC_TABLE_TABLES);
    _dic_table_insert(tb, dbstr, filestr);
}

//顺序绝对不能搞错！
static void _dic_column_insert(struct table * tb, struct column * col)
{
    table_insert_record(tb,
                        &col->c_type,
                        &col->c_size,
                        &col->c_notnull,
                        &col->c_pri_key,
                        col->c_name,
                        col->c_tbname,
                        col->c_dbname,
                        &col->c_offset,
                        col->c_fk_tbname,
                        col->c_fk_colname,
                        &col->c_unique);
}

void dic_column_insert(struct column * col)
{
    struct table * tb;
    tb = table_get_by_name(dic_db, DIC_TABLE_COLUMNS);
    _dic_column_insert(tb, col);
}

//检查名字为dbname的database是否存在
int dic_check_dbname(char * dbname)
{
    struct table * tb = table_get_by_name(dic_db, DIC_TABLE_DATABASE);
    struct column * col = table_get_column(tb, "dbname");
    return check_record_count(col, DIC_DBNAME, DIC_TABLE_DATABASE, dbname);
}

//数据字典存在时读取信息
struct database * _dictionary_initial() {
    struct database * db;
    struct table * tb_db, * tb_tb, * tb_col;
    struct block * b;
    db = _database_initial(DIC_FILENAME);
    b = db->d_block;
    while(b) {
        if(table_get_by_name(db, b->header.tb_name) == NULL) {
            if(strcmp(b->header.tb_name, DIC_TABLE_DATABASE) == 0) {
                tb_db = table_new_instance(db, DIC_TABLE_DATABASE,
                                           sizeof(dic_database_cols) / sizeof(struct column));
                memcpy(tb_db->tb_cols, dic_database_cols, sizeof(dic_database_cols));
                tb_db->tb_record_size = sizeof(struct dic_database);
            } else if(strcmp(b->header.tb_name, DIC_TABLE_TABLES) == 0) {
                tb_tb = table_new_instance(db, DIC_TABLE_TABLES,
                                           sizeof(dic_table_cols) / sizeof(struct column));
                memcpy(tb_tb->tb_cols, dic_table_cols, sizeof(dic_table_cols));
                tb_tb->tb_record_size = sizeof(struct dic_table);
            } else if(strcmp(b->header.tb_name, DIC_TABLE_COLUMNS) == 0) {
                tb_col = table_new_instance(db, DIC_TABLE_COLUMNS,
                                            sizeof(dic_column_cols) / sizeof(struct column));
                memcpy(tb_col->tb_cols, dic_column_cols, sizeof(dic_column_cols));
                tb_col->tb_record_size = sizeof(struct column);
            }
        }
        b = b->prev;
    }
    return db;
}

//数据字典不存在时创建
struct database * _dictionary_create() {
    struct database * db;
    struct table * tb_db, * tb_tb, * tb_col;
    db = _database_create(DIC_FILENAME, DIC_DBNAME, DIC_BLOCK_SIZE);
    //创建表
    tb_db = table_create(db, DIC_TABLE_DATABASE,
                         sizeof(dic_database_cols) / sizeof(struct column),
                         sizeof(struct dic_database));
    memcpy(tb_db->tb_cols, dic_database_cols, sizeof(dic_database_cols));

    tb_tb = table_create(db, DIC_TABLE_TABLES,
                         sizeof(dic_table_cols) / sizeof(struct column),
                         sizeof(struct dic_table));
    memcpy(tb_tb->tb_cols, dic_table_cols, sizeof(dic_table_cols));

    tb_col = table_create(db, DIC_TABLE_COLUMNS,
                          sizeof(dic_column_cols) / sizeof(struct column),
                          sizeof(struct column));
    memcpy(tb_col->tb_cols, dic_column_cols, sizeof(dic_column_cols));

    _dic_database_insert(tb_db, DIC_DBNAME, DIC_FILENAME);
    _dic_table_insert(tb_tb, DIC_TABLE_DATABASE, DIC_DBNAME);
    _dic_table_insert(tb_tb, DIC_TABLE_TABLES, DIC_DBNAME);
    _dic_table_insert(tb_tb, DIC_TABLE_COLUMNS, DIC_DBNAME);

    for(int i = 0; i < tb_db->tb_col_nr; i++)
        _dic_column_insert(tb_col, &dic_database_cols[i]);

    for(int i = 0; i < tb_tb->tb_col_nr; i++)
        _dic_column_insert(tb_col, &dic_table_cols[i]);

    for(int i = 0; i < tb_col->tb_col_nr; i++)
        _dic_column_insert(tb_col, &dic_column_cols[i]);

    return db;
}

static int get_file_length(char * fname)
{
    FILE * fp;
    fp = fopen(fname, "rb");
    if(fp == NULL)
        return -1;

    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    fclose(fp);

    return len;
}

void initial_dictionary()
{
    if(access(DIC_FILENAME, 0) == 0) {
        if(get_file_length(DIC_FILENAME) == 0) {
            //数据字典存在但长度为0，说明文件损坏
            remove(DIC_FILENAME);
            dic_db = _dictionary_create();
        } else {
            dic_db = _dictionary_initial();
        }
    } else {
        dic_db = _dictionary_create();
    }
}
