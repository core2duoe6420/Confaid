#ifndef __LINUX__

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")
#include <WinSock2.h>
#define S_ADDR S_un.S_addr

#else

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define S_ADDR s_addr

#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "sql.h"
#include "buffer.h"
#include "datafile.h"

#ifndef __LINUX__

int WSA_initial()
{
    WORD ver;
    WSADATA WSAData;
    ver = MAKEWORD(2, 2);
    if(WSAStartup(ver, &WSAData) != 0) {
        fprintf(stderr, "Fatal Error WSA initial fail: %s\n",
                strerror(errno));
        exit(1);
    }
    return 0;
}

void WSA_close()
{
    WSACleanup();
}

void close_socket(int sockfd)
{
    closesocket(sockfd);
}

#else

int WSA_initial()
{
    return 0;
}

void WSA_close()
{
}

void close_socket(int sockfd)
{
    close(sockfd);
}
#endif

int server_socket_create(char * server_ip, int port)
{
    int server_fd;
    if((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        fprintf(stderr, "Fatal Error create server socket fail: %s\n",
                strerror(errno));
        exit(1);
    }

    int value = 1;
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                  (const char *)&value, sizeof(value)) != 0) {
        fprintf(stderr, "Error when setting socket\n");
        exit(1);
    }

    struct sockaddr_in my_addr;
    my_addr.sin_addr.S_ADDR = inet_addr(server_ip);
    my_addr.sin_port = htons(port);
    my_addr.sin_family = AF_INET;
    memset(&my_addr.sin_zero, 0, sizeof(my_addr.sin_zero));

    if(bind(server_fd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1) {
        fprintf(stderr, "Fatal Error bind server client fail: %s\n",
                strerror(errno));
        exit(1);
    }

    char* bind_ip = inet_ntoa(my_addr.sin_addr);
    printf("bind successfully. ip:%s, port:%d\n", bind_ip, ntohs(my_addr.sin_port));

    return server_fd;
}

int server_socket_listen(int server_fd)
{
    if(listen(server_fd, 5) == -1) {
        fprintf(stderr, "Fatal Error listen server client fail: %s\n",
                strerror(errno));
        exit(1);
    }
    return 0;
}

//发送内容为字符串的buf，长度为字符串长度，失败会关闭sockfd
int socket_send_buf(int sockfd, char * sendbuf)
{
    int buflen;
    buflen = strlen(sendbuf);
    if(send(sockfd, sendbuf, buflen, 0) != buflen) {
        fprintf(stderr, "send fail");
        close_socket(sockfd);
        return 1;
    }
    return 0;
}

int socket_send_dataset(int sockfd, struct dataset * ds)
{
    char sendbuf[10240];
    int bufpos = 0;

    sprintf(sendbuf, "<info>%s</info>", ds->info);
    if(socket_send_buf(sockfd, sendbuf))
        return 1;

    if(ds->result == 0) {
        bufpos += sprintf(sendbuf + bufpos, "<columns>");
        for(int i = 0; i < ds->column_set->len; i++) {
            struct column * col;
            col = column_set_get_column(ds->column_set, i);
            bufpos += sprintf(sendbuf + bufpos, "<column>%s</column>", col->c_name);
        }
        bufpos += sprintf(sendbuf + bufpos, "</columns>");

        if(socket_send_buf(sockfd, sendbuf))
            return 1;

        for(int rowid = 0; rowid < ds->row_set->len; rowid++) {
            bufpos = 0;
            bufpos += sprintf(sendbuf + bufpos, "<row>");
            struct row_struct * row;
            row = dataset_get_row(ds, rowid);
            for(int colid = 0; colid < ds->column_set->len; colid++) {
                struct column * col;
                void * value;
                col = column_set_get_column(ds->column_set, colid);
                value = row_struct_get_value_by_id(row, colid);

                bufpos += sprintf(sendbuf + bufpos, "<data>");

                switch(col->c_type) {
                case COL_INT:
                    if(col->c_notnull != 0 || *(int*)value != INT_NULL)
                        bufpos += sprintf(sendbuf + bufpos, "%d", *(int*)value);
                    break;
                case COL_DOUBLE:
                    if(col->c_notnull != 0 || *(double*)value != DOUBLE_NULL)
                        bufpos += sprintf(sendbuf + bufpos, "%lf", *(double*)value);
                    break;
                case COL_CHAR:
                    if(col->c_notnull != 0 || strcmp((char*)value, CHAR_NULL) != 0)
                        bufpos += sprintf(sendbuf + bufpos, "%s", (char*)value);
                    break;
                }

                bufpos += sprintf(sendbuf + bufpos, "</data>");
            }
            bufpos += sprintf(sendbuf + bufpos, "</row>");

            if(socket_send_buf(sockfd, sendbuf))
                return 1;
        }
    }
    //结束标记
    sprintf(sendbuf, "end");
    if(socket_send_buf(sockfd, sendbuf))
        return 1;

    return 0;
}

int main()
{
    initial_buffer(1024 * 1024, 4096);
    initial_dictionary();

    char server_ip[32];
    int server_port;
    WSA_initial();
    printf("input ip and port:");
    scanf("%s%d", server_ip, &server_port);

    int server_fd;
    server_fd = server_socket_create(server_ip, server_port);
    server_socket_listen(server_fd);

    while(1) {
        int client_fd, addrlen = sizeof(struct sockaddr_in);
        struct sockaddr_in client_addr;
        //accept参数不初始化会出现Invalid arguments错误
        memset(&client_addr, 0, sizeof(struct sockaddr_in));
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);

        if(client_fd == -1) {
            fprintf(stderr, "Error get client socket fail: %s\n",
                    strerror(errno));
            break;
        }

        char* client_ipstr = inet_ntoa(client_addr.sin_addr);
        printf("get socket:%d, client ip:%s, port:%d\n",
               client_fd, client_ipstr, ntohs(client_addr.sin_port));

        //设置超时
        struct timeval timeout = {10, 0};
        if(setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO,
                      (const char *)&timeout, sizeof(struct timeval)) != 0) {
            fprintf(stderr, "Error when setting timeout\n");
            break;
        }

        char sqlbuf[1024];
        int recvn;
        int closed = 0;
        while((recvn = recv(client_fd, sqlbuf, sizeof(sqlbuf), 0)) > 0) {
            //可能会有上次遗留的缓存
            sqlbuf[recvn] = 0;

            if(strcmp(sqlbuf, "flush;") == 0) {
                buffer_flush();
                continue;
            } else if(strcmp(sqlbuf, "close;") == 0) {
                close_socket(client_fd);
                closed = 1;
                break;
            }

            struct dataset * ds;
            ds = run_sql(sqlbuf);
            socket_send_dataset(client_fd, ds);
            dataset_destroy(ds);
        }
        printf("socket %d closed\n", client_fd);
        if(closed)
            break;
    }

    close_socket(server_fd);
    WSA_close();

    printf("Confaid is closing\n");
    buffer_flush();
    struct database * db = db_set;
    while(db) {
        fclose(db->d_df->file);
        db = db->d_next_db;
    }

    return 0;
}