#ifndef __RNODE_H
#define __RNODE_H

#include <stddef.h>

//for struct block
#include "database.h"

#define RNODE_ITEM 3

#define MAGIC_DELETE 0xAA
#define MAGIC_USING 0xBB
#define MAGIC_INDEX 0xCC

struct rnode_d {
    int magic;
    int r_zone[RNODE_ITEM];
};

/* rnode有两种用途，一种索引记录
 * 一种是在rnode索引表大小不够时
 * 记录下一级索引的块号
 */
#define RNODE_INDEX 1
#define RNODE_RECORD 2

struct rnode_m {
    struct rnode_d r_node;
    int type;
    struct block * r_block;
    /* 从pid和idx计算offset的方法：
     * offset = r_block->header.block_start +
     *          r_pieceid * r_block->header.piece_size +
     *          r_idx_inp * sizeof(struct rnode_d)
     */
    int r_pieceid;				//所在块内的pid
    int r_idx_inp;				//片内索引
    int r_offset;				//所在数据文件的全局偏移量

    int r_last_idx_piece;		//上次分配空间所用的pid，加速分配空间
};

struct rnode_m * rnode_get_usable(struct block * b);
int rnode_alloc_piece(struct rnode_m * rn);
int rnode_remove(struct rnode_m * rn);
void rnode_iter_initial(struct block * b);
struct rnode_m * rnode_iter_block(struct block * b);
void rnode_destroy(struct rnode_m * rn);

#endif