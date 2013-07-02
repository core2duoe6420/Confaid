#ifndef __DATABASE_H
#define __DATABASE_H

#include <stddef.h>

#include "global.h"
#include "bitmap.h"

struct column;

#define DATABASE_HEADER_SIZE 4096
//����DBʱû��ָ��BLOCK_SIZEʱʹ�ã���λM
#define DEFAULT_BLOCK_SIZE 10

#define BLOCK_DELETED 3

struct block_header {
    char tb_name[NAMEMAX_LEN + 1]; 	//�������ı���
    int type;						//������ 1-�� 2-����
    size_t piece_size; 				//����Ƭ��С
    int piecenr; 					//����Ƭ����
    int block_start;				//����ʼƫ�Ƶ�ַ
    int start_pid;					//��һ��������ݵ�Ƭ�ı��
    size_t bitmap_size;				//Ƭλͼռ�õĿռ䣬��λ�ֽ�
    int next_block;					//��һ�������ʼ��ַ
    int tb_continue;				//����ͬһ�ű����һ����ĵ�ַ����������Ϊ0
    int rnode_per_piece;			//ÿ���ڴ�ŵ�rnode���� rnode������ض�
    int rnode_nr;
};

struct block {
    struct block_header header;
    struct bitmap bitmap;
    int bitmap_offset;
    struct database * db;
    struct block * next;
    struct block * prev;
    //ͬһ�ű�ĸ���block�����������ֶ���
    struct block * tb_next;
    struct block * tb_prev;

    int last_get_rnode_pid;			//���ڷ���rnodeʱ���ٶ�λƬ
    int iter_rnode_pid;				//���ڵ���rnodeʱ���ٶ�λƬ
    int iter_rnode_idx;				//���ڵ���rnodeʱ���ٶ�λƬ������
};

//��Щ��Ϣ��Ӳ����
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