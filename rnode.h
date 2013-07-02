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

/* rnode��������;��һ��������¼
 * һ������rnode�������С����ʱ
 * ��¼��һ�������Ŀ��
 */
#define RNODE_INDEX 1
#define RNODE_RECORD 2

struct rnode_m {
    struct rnode_d r_node;
    int type;
    struct block * r_block;
    /* ��pid��idx����offset�ķ�����
     * offset = r_block->header.block_start +
     *          r_pieceid * r_block->header.piece_size +
     *          r_idx_inp * sizeof(struct rnode_d)
     */
    int r_pieceid;				//���ڿ��ڵ�pid
    int r_idx_inp;				//Ƭ������
    int r_offset;				//���������ļ���ȫ��ƫ����

    int r_last_idx_piece;		//�ϴη���ռ����õ�pid�����ٷ���ռ�
};

struct rnode_m * rnode_get_usable(struct block * b);
int rnode_alloc_piece(struct rnode_m * rn);
int rnode_remove(struct rnode_m * rn);
void rnode_iter_initial(struct block * b);
struct rnode_m * rnode_iter_block(struct block * b);
void rnode_destroy(struct rnode_m * rn);

#endif