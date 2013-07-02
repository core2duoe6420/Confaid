#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <glib.h>

#include "database.h"
#include "datafile.h"
#include "table.h"
#include "buffer.h"
#include "sql.h"

struct database * cur_db = NULL;
struct database * db_set = NULL;


void piece_read_buffer(struct piece * p)
{
    struct block * b = p->p_block;
    int offset = b->header.block_start +
                 b->header.piece_size * p->p_pid;
    structure_read_buffer(b->db->d_df, p->p_data, b->header.piece_size, offset);
}

void piece_write_buffer(struct piece * p)
{
    struct block * b = p->p_block;
    int offset = b->header.block_start +
                 b->header.piece_size * p->p_pid;
    structure_write_buffer(b->db->d_df, p->p_data, b->header.piece_size, offset);
}

void block_read_buffer(struct block * b, int offset)
{
    structure_read_buffer(b->db->d_df, &b->header, sizeof(struct block_header), offset);
}

void block_write_buffer(struct block * b, int offset)
{
    structure_write_buffer(b->db->d_df, &b->header, sizeof(struct block_header), offset);
}

void database_header_read_buffer(struct database * db)
{
    structure_read_buffer(db->d_df, &db->d_header, sizeof(struct database_header), 0);
}

void database_header_write_buffer(struct database * db)
{
    structure_write_buffer(db->d_df, &db->d_header, sizeof(struct database_header), 0);
}

struct piece * piece_new_instance(struct block * b, int pid) {
    struct piece * p;
    p = (struct piece *)g_malloc(sizeof(struct piece));

    assert(p);

    p->p_data = (char *)g_malloc(b->header.piece_size);

    assert(p->p_data);

    memset(p->p_data, 0, b->header.piece_size);

    p->p_block = b;
    p->p_pid = pid;
    return p;
}

void piece_destroy(struct piece * p)
{
    g_free(p->p_data);
    g_free(p);
}

void bitmap_read_buffer(struct datafile * df, struct bitmap * bm, int offset)
{
    int bytes = (bm->bits_nr + 7) / 8;
    int read = 0, size = 0, d_offset = 0;
    while(bytes > 0) {
        size = bytes > BUFFER_BLOCK_SIZE ? BUFFER_BLOCK_SIZE : bytes;
        read = structure_read_buffer(df, bm->bits + d_offset, size, offset + d_offset);
        d_offset += read;
        bytes -= read;
    }
}

void bitmap_write_buffer(struct datafile * df, struct bitmap * bm, int offset)
{
    int bytes = (bm->bits_nr + 7) / 8;
    int read = 0, size = 0, d_offset = 0;
    while(bytes > 0) {
        size = bytes > BUFFER_BLOCK_SIZE ? BUFFER_BLOCK_SIZE : bytes;
        read = structure_write_buffer(df, bm->bits + d_offset, size, offset + d_offset);
        d_offset += read;
        bytes -= read;
    }
}

int block_get_piece(struct block * b)
{
    int usable_pid;
    usable_pid = bitmap_get_first_usable(&b->bitmap);

    //DEBUG，无限的空间！！！
    assert(usable_pid > 0);

    bitmap_write_buffer(b->db->d_df, &b->bitmap, b->bitmap_offset);
    return usable_pid;
}

//该函数仅修改位图，不会操作片内数据
void block_release_piece(struct block * b, int pid)
{
    //释放没有分配过的块是非法调用，数据不一致！
    assert(bitmap_test(&b->bitmap, pid));

    bitmap_clear(&b->bitmap, pid);

    bitmap_write_buffer(b->db->d_df, &b->bitmap, b->bitmap_offset);

}

//将磁盘中片内数据清0
void piece_set_zero(struct block * b, int pid)
{
    struct piece * dirtyp;
    dirtyp = piece_new_instance(b, pid);
    piece_write_buffer(dirtyp);
    piece_destroy(dirtyp);
}

static void block_header_create(struct block * b, int offset, int next_block,
                                char * tb_name, size_t piece_size)
{
    assert(sizeof(struct block_header) <= piece_size);
    struct block_header * bh = &b->header;
    int block_size;
    block_size = b->db->d_header.dh_block_size;
    bh->type = 1;
    strcpy(bh->tb_name, tb_name);
    bh->piece_size = piece_size;
    bh->piecenr = (block_size + piece_size - 1) / piece_size;
    bh->rnode_per_piece = piece_size / sizeof(struct rnode_d);
    bh->tb_continue = 0;
    bh->next_block = next_block;
    bh->bitmap_size = (bh->piecenr + 7) / 8;
    bh->start_pid = (bh->bitmap_size + piece_size - 1) / piece_size + 1;
    bh->block_start = offset;
    bh->rnode_nr = 0;

    block_write_buffer(b, offset);

    b->bitmap_offset = offset + piece_size;
    bitmap_create(&b->bitmap, bh->piecenr);
    for(int i = 0; i < bh->start_pid; i++)
        bitmap_set(&b->bitmap, i);

    bitmap_write_buffer(b->db->d_df, &b->bitmap, b->bitmap_offset);
}

static void block_header_initial(struct block * b, int offset)
{
    struct block_header * bh;
    bh = &b->header;
    block_read_buffer(b, offset);

    //已删除的block不需要读取位图
    if(bh->type == BLOCK_DELETED)
        return;

    bitmap_create(&b->bitmap, bh->piecenr);
    b->bitmap_offset = bh->block_start + bh->piece_size;
    bitmap_read_buffer(b->db->d_df, &b->bitmap, b->bitmap_offset);
    bitmap_count_usable(&b->bitmap);
}

//该函数会将block->db设置为db，但不会操作db中的block链表
static struct block * block_new_instance(struct database * db) {
    struct block * b;
    b = (struct block *)g_malloc0(sizeof(struct block));

    assert(b);

    b->db = db;
    return b;
}

//该函数会将b插入到db的block链表中
static void block_bind_database(struct block * b, struct database * db)
{
    b->db = db;
    if(db) {
        b->prev = db->d_block;
        if(db->d_block)
            db->d_block->next = b;
        db->d_block = b;
    }
}

static void block_destroy(struct block * b)
{
    if(b->bitmap.bits)
        g_free(b->bitmap.bits);
    g_free(b);
}

//从文件中读取所有block信息
int database_read_block(struct database * db)
{
    struct block * b;
    int offset = DATABASE_HEADER_SIZE;

    if(db->d_header.dh_filelen == offset)
        return 0;

    do {
        b = block_new_instance(db);
        block_bind_database(b, db);
        block_header_initial(b, offset);
        offset = b->header.next_block;

        if(b->header.type == BLOCK_DELETED)
            continue;

        struct block * odd;
        odd = b->prev;
        while(odd) {
            if(strcmp(b->header.tb_name, odd->header.tb_name) == 0) {
                b->tb_prev = odd;
                odd->tb_next = b;
            }
            odd = odd->prev;
        }

    } while(offset);
    return 0;
}

//先查找block链表，如果有BLCOK_DELETED则使用，如果没有在数据文件末尾创建一个
struct block * database_create_block(struct database * db, char * tb_name, size_t piece_size) {
    struct block * b = db->d_block;
    int newblock = 0;
    while(b) {
        if(b->header.type == BLOCK_DELETED)
            break;
        b = b->prev;
    }
    //没有删除的块，创建一个
    if(b == NULL) {
        newblock = 1;
        b = block_new_instance(db);
        block_bind_database(b, db);
        assert(b);
    }
    int block_start = newblock ? db->d_header.dh_filelen : b->header.block_start;
    int next_block = newblock ? 0 : b->header.next_block;
    block_header_create(b, block_start, next_block, tb_name, piece_size);

    struct block * old;

    old = b->prev;
    while(old) {
        //同一张表
        if(strcmp(tb_name, old->header.tb_name) == 0) {
            if(old->header.tb_continue == 0) {
                old->header.tb_continue = db->d_header.dh_filelen;
                block_write_buffer(old, old->header.block_start);
                old->tb_next = b;
                b->tb_prev = old;
            }
        }
        if(newblock && old->header.next_block == 0) {
            old->header.next_block = db->d_header.dh_filelen;
            block_write_buffer(old, old->header.block_start);
        }
        old = old->prev;
    }

    if(newblock) {
        db->d_header.dh_filelen += db->d_header.dh_block_size;
        db->d_header.dh_blocknr++;
        database_header_write_buffer(db);
    }
    return b;
}

//block信息也会读取完成
struct database * _database_initial(char * db_file) {
    struct database * db;
    db = (struct database *)g_malloc0(sizeof(struct database));
    assert(db);

    db->d_df = datafile_open(db_file);

    database_header_read_buffer(db);

    db->d_block = NULL;
    db->d_table = NULL;
    database_read_block(db);

    db->d_next_db = db_set;
    db_set = db;

    return db;
}

//_database_create和_database_initial都会将db插入到db_set链表中
struct database * _database_create(char * db_file, char * db_name, size_t block_size) {
    struct database * db;
    db = (struct database *)g_malloc0(sizeof(struct database));
    assert(db);

    db->d_df = datafile_create(db_file);

    strcpy(db->d_header.dh_name, db_name);
    db->d_header.dh_block_size = block_size;
    db->d_header.dh_blocknr = 0;
    db->d_header.dh_filelen = DATABASE_HEADER_SIZE;
    db->d_block = NULL;
    db->d_table = NULL;
    database_header_write_buffer(db);

    db->d_next_db = db_set;
    db_set = db;

    return db;
}

struct database * normal_database_create(char * db_name, size_t block_size) {
    char db_file[NAMEMAX_LEN + 1];
    sprintf(db_file, "%s.cdf", db_name);

    struct database * db;
    db = _database_create(db_file, db_name, block_size);
    //插入到数据字典中
    dic_database_insert(db_name, db_file);
    return db;
}

struct database * normal_database_open(char * db_name) {
    struct database * db;

    char * dbfile;

    struct dataset * ds;
    struct row_struct * row;
    ds = run_sql("SELECT dbfile FROM dictionary.databases WHERE dbname=='%s';", db_name);
    row = (struct row_struct *)g_ptr_array_index(ds->row_set, 0);
    dbfile = (char*)row->data[0];

    db = _database_initial(dbfile);

    dataset_destroy(ds);

    assert(db);

    struct block * b = db->d_block;

    while(b) {
        struct table * tb;
        char * tbname;
        tbname = b->header.tb_name;
        tb = table_get_by_name(db, tbname);

        if(tb == NULL) {
            ds = run_sql("SELECT * FROM dictionary.columns WHERE dbname=='%s' AND tbname=='%s';",
                         db_name, tbname);
            tb = table_new_instance(db, b->header.tb_name, ds->row_set->len);
            int size = 0;
            for(int i = 0; i < ds->row_set->len; i++) {
                row = (struct row_struct *)g_ptr_array_index(ds->row_set, i);
                memcpy(&tb->tb_cols[i], row->data[0], sizeof(struct column));
                int temp = tb->tb_cols[i].c_offset + tb->tb_cols[i].c_size;
                size = temp > size ? temp : size;
            }
            dataset_destroy(ds);
            tb->tb_record_size = size;
        }
        b = b->prev;
    }

    return db;
}

void database_close(char * dbname)
{
    struct database * db = db_set, * prev = db_set;
    while(db) {
        if(strcmp(db->d_header.dh_name, dbname) == 0)
            break;
        prev = db;
        db = db->d_next_db;
    }
    //数据字典不允许关闭
    if(db == dic_db)
        return;

    //数据库已经打开，关闭
    if(db) {
        //是否是当前数据库？
        if(db == cur_db)
            cur_db = NULL;
        //释放所有该数据库缓存
        buffer_database_delete(db);
        //释放所有block
        struct block * b = db->d_block, * tmpb;
        while(b) {
            tmpb = b;
            b = b->prev;
            block_destroy(tmpb);
        }

        //释放所有table
        struct table * tb = db->d_table, * tmptb;
        while(tb) {
            tmptb = tb;
            tb = tb->tb_next;
            table_destroy(tmptb);
        }

        if(prev == db_set)
            db_set = db->d_next_db;
        else
            prev->d_next_db = db->d_next_db;

        //关闭数据文件
        datafile_close(db->d_df);
        g_free(db);
    }
}

void database_drop(char * dbname)
{
    //先关闭数据库
    database_close(dbname);

    struct dataset * ds;
    ds = run_sql("SELECT tbname FROM dictionary.tables WHERE dbname=='%s';", dbname);
    for(int rowid = 0; rowid < ds->row_set->len; rowid++) {
        struct row_struct * row;
        row = (struct row_struct *)g_ptr_array_index(ds->row_set, rowid);

        run_sql("DELETE FROM dictionary.columns WHERE dbname=='%s' AND tbname=='%s';",
                dbname, row->data[0]);
    }
    dataset_destroy(ds);

    run_sql("DELETE FROM dictionary.tables WHERE dbname=='%s';", dbname);

    ds = run_sql("SELECT dbfile FROM dictionary.databases WHERE dbname=='%s';", dbname);
    remove((char*)((struct row_struct *)g_ptr_array_index(ds->row_set, 0))->data[0]);
    dataset_destroy(ds);

    run_sql("DELETE FROM dictionary.databases WHERE dbname=='%s';", dbname);
}