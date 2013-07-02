#ifndef __DATABASE_H
#define __DATABASE_H

#include <stddef.h>

#include "global.h"
#include "bitmap.h"

struct column;

#define DATABASE_HEADER_SIZE 4096
//创建DB时没有指定BLOCK_SIZE时使用，单位M
#define DEFAULT_BLOCK_SIZE 10

#define BLOCK_DELETED 3

struct block_header {
    char tb_name[NAMEMAX_LEN + 1]; 	//块所属的表名
    int type;						//块类型 1-表 2-索引
    size_t piece_size; 				//块内片大小
    int piecenr; 					//块内片总数
    int block_start;				//块起始偏移地址
    int start_pid;					//第一个存放数据的片的编号
    size_t bitmap_size;				//片位图占用的空间，单位字节
    int next_block;					//下一个块的起始地址
    int tb_continue;				//属于同一张表的下一个块的地址，不存在则为0
    int rnode_per_piece;			//每块内存放的rnode数量 rnode不允许截断
    int rnode_nr;
};

struct block {
    struct block_header header;
    struct bitmap bitmap;
    int bitmap_offset;
    struct database * db;
    struct block * next;
    struct block * prev;
    //同一张表的各个block链在这两个字段中
    struct block * tb_next;
    struct block * tb_prev;

    int last_get_rnode_pid;			//用于分配rnode时快速定位片
    int iter_rnode_pid;				//用于迭代rnode时快速定位片
    int iter_rnode_idx;				//用于迭代rnode时快速定位片内索引
};

//这些信息在硬盘中
struct database_header {
    char dh_name[NAMEMAX_LEN + 1];
    size_t dh_filelen;
    int dh_blocknr;
    size_t dh_block_size;
};

struct database {
    struct database_header d_header;
    struct datafile * d_df;
    struct block * d_block;
    struct table * d_table;
    struct database * d_next_db;
};

struct piece {
    char * p_data;
    struct block * p_block;
    int p_pid;
};

int block_get_piece(struct block * b);
struct piece * piece_new_instance(struct block * b, int pid);
void piece_read_buffer(struct piece * p);
void piece_write_buffer(struct piece * p);
void piece_destroy(struct piece * p);
void bitmap_write_buffer(struct datafile * df, struct bitmap * bm, int offset);
void block_release_piece(struct block * b, int pid);
void piece_set_zero(struct block * b, int pid);

struct block * database_create_block(struct database * db, char * tb_name, size_t piece_size);
struct database * _database_create(char * db_file, char * db_name, size_t block_size);
struct database * _database_initial(char * db_file);
struct database * normal_database_create(char * db_name, size_t block_size);
struct database * normal_database_open(char * db_name);
void database_close(char * dbname);
void database_drop(char * dbname);

//dictionary.c
void initial_dictionary();
void dic_column_insert(struct column * col);
void dic_table_insert(char * dbstr, char * filestr);
void dic_database_insert(char * dbstr, char * filestr);

int dic_check_dbname(char * dbname);



extern struct database * dic_db;
extern struct database * cur_db;
extern struct database * db_set;


#endif