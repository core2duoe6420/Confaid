#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <glib.h>

#include "rnode.h"
#include "buffer.h"

void rnode_read_buffer(struct rnode_m * rn)
{
    struct datafile * df = rn->r_block->db->d_df;
    structure_read_buffer(df, &rn->r_node, sizeof(struct rnode_d), rn->r_offset);
}

void rnode_write_buffer(struct rnode_m * rn)
{
    struct datafile * df = rn->r_block->db->d_df;
    structure_write_buffer(df, &rn->r_node, sizeof(struct rnode_d), rn->r_offset);
}

static struct rnode_m * rnode_new_instance(struct block * b) {
    assert(b->header.piece_size % sizeof(struct rnode_d) == 0);

    struct rnode_m * rn;
    rn = (struct rnode_m *)g_malloc(sizeof(struct rnode_m));

    assert(rn);

    rn->r_block = b;
    rn->type = 0;
    rn->r_idx_inp = 0;
    rn->r_offset = 0;
    rn->r_pieceid = 0;
    rn->r_last_idx_piece = 0;
    return rn;
}

void rnode_destroy(struct rnode_m * rn)
{
    g_free(rn);
}

void rnode_bind_piece(struct rnode_m * rn, int piece_id, int idx_inp)
{
    struct block * b = rn->r_block;
    rn->r_pieceid = piece_id;
    rn->r_idx_inp = idx_inp;
    rn->r_offset = b->header.block_start +
                   rn->r_pieceid * b->header.piece_size +
                   rn->r_idx_inp * sizeof(struct rnode_d);
}

static int rnode_create_index(struct block * b, int r_pid)
{
    struct rnode_m * rn;
    rn = rnode_new_instance(b);
    rnode_bind_piece(rn, r_pid, b->header.rnode_per_piece - 1);

    int usable_pid;
    usable_pid = block_get_piece(b);

    rn->r_node.magic = MAGIC_INDEX;
    rn->r_node.r_zone[0] = usable_pid;
    for(int i = 1; i < RNODE_ITEM; i++)
        rn->r_node.r_zone[i] = 0;

    rnode_write_buffer(rn);

    rnode_destroy(rn);

    return usable_pid;
}

struct rnode_m * rnode_get_usable(struct block * b) {
    struct rnode_m * rn;
    int piece_id, idx_inp;

    //û�л�����Ϣ
    if(b->last_get_rnode_pid == 0) {
        //���ڵ�һ��������ݵ�Ƭ�ض���rnode
        piece_id = b->header.start_pid;
        //�鴴�����һ�ε���ʱ��һ��λͼ����û����1
        if(bitmap_test(&b->bitmap, piece_id) == 0) {
            bitmap_set(&b->bitmap, piece_id);
            bitmap_write_buffer(b->db->d_df, &b->bitmap, b->bitmap_offset);
        }
    } else {
        piece_id = b->last_get_rnode_pid;
    }

    idx_inp = 0;
    rn = rnode_new_instance(b);
    while(1) {
        rnode_bind_piece(rn, piece_id, idx_inp);
        rnode_read_buffer(rn);
        if(rn->r_node.magic != MAGIC_USING &&
           rn->r_node.magic != MAGIC_INDEX) {
            memset(&rn->r_node, 0, sizeof(struct rnode_d));
            rn->r_node.magic = MAGIC_USING;
            b->last_get_rnode_pid = piece_id;
            return rn;
        }
        idx_inp++;
        /* �Ѿ��ﵽƬ�����һ��������������������������򴴽�����
         * ��ʱ������Ƭ��ȫ������ļ����������Ϊ��block_get_piece��
         * assert��
         */
        if(idx_inp == b->header.rnode_per_piece - 1) {
            rnode_bind_piece(rn, piece_id, idx_inp);
            rnode_read_buffer(rn);
            if(rn->r_node.magic == MAGIC_INDEX) {
                piece_id = rn->r_node.r_zone[0];
                idx_inp = 0;
                continue;
            } else {
                //��������
                piece_id = rnode_create_index(b, piece_id);
                idx_inp = 0;
            }
        }
    }
    return NULL;
}

/* �������ÿ����һ��Ϊrnode����һ��Ƭ
 * �ﵽ���һ����ʱ�ᴴ����һ������
 * ����ֵ����0��ʾ�ҵ���pid������0����
 */
int rnode_alloc_piece(struct rnode_m * rn)
{
    struct block * b = rn->r_block;
    int item;
    int * arridx;
    struct piece * curp = NULL;
    int ret;

    //������һ�η���ļ�¼��ֱ�ӴӸ�Ƭ��ʼ����
    if(rn->r_last_idx_piece) {
        curp = piece_new_instance(b, rn->r_last_idx_piece);
        piece_read_buffer(curp);
        arridx = (int *)curp->p_data;
        item = b->header.piece_size / sizeof(int) - 1;
    } else {
        arridx = rn->r_node.r_zone;
        item = RNODE_ITEM - 1;
    }

    while(1) {
        int i;
        for(i = 0; i < item; i++) {
            if(arridx[i] == 0) {
                arridx[i] = block_get_piece(b);
                //д�����ݣ���Ҫ���ֶ���
                if(arridx == rn->r_node.r_zone)
                    rnode_write_buffer(rn);
                else
                    piece_write_buffer(curp);

                ret = arridx[i];
                if(curp) {
                    rn->r_last_idx_piece = curp->p_pid;
                    piece_destroy(curp);
                }
                return ret;
            }
        }
        //ֱ������û�ҵ������һ������һ������
        int create_idx;
        create_idx = 0;
        if(arridx[i] == 0) {
            //������û������
            create_idx = 1;
            arridx[i] = block_get_piece(b);
            if(arridx == rn->r_node.r_zone)
                rnode_write_buffer(rn);
            else
                piece_write_buffer(curp);
        }

        int pid = arridx[i];
        if(curp)
            piece_destroy(curp);

        curp = piece_new_instance(b, pid);
        //�½�������������Ҫ���ļ��ж�ȡ����
        if(create_idx == 0)
            piece_read_buffer(curp);
        arridx = (int *)curp->p_data;
        item = b->header.piece_size / sizeof(int) - 1;
    }
    return 0;
}

int rnode_remove(struct rnode_m * rn)
{
    struct block * b = rn->r_block;
    int item = RNODE_ITEM - 1;
    int * arridx = rn->r_node.r_zone;
    struct piece * curp = NULL, * dirtyp = NULL;
    int total = 0;

    while(1) {
        int i;
        for(i = 0; i < item; i++) {
            //����0����ֹ
            if(arridx[i] == 0) {
                if(curp)
                    piece_destroy(curp);
                //rn������ȫ�����㣬д�ش���
                rn->r_node.magic = MAGIC_DELETE;
                rnode_write_buffer(rn);
                b->last_get_rnode_pid = rn->r_pieceid;
                return total;
            }
            total++;

            block_release_piece(b, arridx[i]);
            piece_set_zero(b, arridx[i]);

            arridx[i] = 0;
        }

        //���������ڣ�����Ϊֹ
        if(arridx[i] == 0) {
            if(curp)
                piece_destroy(curp);
            return total;
        }
        //�������ڣ�����
        int pid = arridx[i];
        arridx[i] = 0;
        if(curp)
            piece_destroy(curp);

        curp = piece_new_instance(b, pid);
        piece_read_buffer(curp);
        //��һ���������Ѿ���curp->data���ˣ������ϵ����ݣ��������У���������
        block_release_piece(b, pid);
        piece_set_zero(b, pid);

        arridx = (int *)curp->p_data;
        item = b->header.piece_size / sizeof(int) - 1;
    }
    return 0;
}

void rnode_iter_initial(struct block * b)
{
    b->iter_rnode_idx = -1;
    b->iter_rnode_pid = b->header.start_pid;
}

/* ����һ�����ڵ�����rnode��ÿ����һ����ǰ��һ��rnode
 * ͨ��b->iter_rnode_pid��b->iter_rnode_idx������һ��rnodeλ��
 * ע��rnode��malloc����������free
 */
struct rnode_m * rnode_iter_block(struct block * b) {
    struct rnode_m * rn;
    rn = rnode_new_instance(b);
    do {
        b->iter_rnode_idx++;
        assert(b->iter_rnode_idx < b->header.rnode_per_piece);

        rnode_bind_piece(rn, b->iter_rnode_pid, b->iter_rnode_idx);
        rnode_read_buffer(rn);

        if(rn->r_node.magic == MAGIC_INDEX) {
            b->iter_rnode_pid = rn->r_node.r_zone[0];
            b->iter_rnode_idx = -1;
        }

        //������MAGICֵ��������ֹ
        int magic = rn->r_node.magic;
        if(magic != MAGIC_DELETE && magic != MAGIC_INDEX && magic != MAGIC_USING) {
            g_free(rn);
            return NULL;
        }

    } while(rn->r_node.magic != MAGIC_USING);

    return rn;
}