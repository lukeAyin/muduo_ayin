//
// Created by ayin on 2021/12/14.
//

#ifndef AYIN_MUDUO_HTTP_CONN_H
#define AYIN_MUDUO_HTTP_CONN_H
#include <mysql++/mysql++.h>
#include <string>
#include <stdio.h>
#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpConnection.h"
#include "muduo/net/TcpServer.h"
using namespace muduo;
using namespace muduo::net;
class http_conn
{
public:
    static const int FILENAME_LEN = 200;
    static const int READ_BUFFER_SIZE = 2048;
    static const int WRITE_BUFFER_SIZE = 1024;
    enum METHOD
    {
        GET = 0,
        POST,
        HEAD,
        PUT,
        DELETE,
        TRACE,
        OPTIONS,
        CONNECT,
        PATH
    };
    enum CHECK_STATE
    {
        CHECK_STATE_REQUESTLINE = 0,
        CHECK_STATE_HEADER,
        CHECK_STATE_CONTENT
    };
    enum HTTP_CODE
    {
        NO_REQUEST,
        GET_REQUEST,
        BAD_REQUEST,
        NO_RESOURCE,
        FORBIDDEN_REQUEST,
        FILE_REQUEST,
        INTERNAL_ERROR,
        CLOSED_CONNECTION
    };
    enum LINE_STATUS
    {
        LINE_OK = 0,
        LINE_BAD,
        LINE_OPEN
    };
public:
    http_conn(EventLoop* loop,const InetAddress& listenAddr );
    ~http_conn(){};
public:
    void init(int sockfd, const InetAddress &addr, char *, int, int, string user, string passwd, string sqlname);
    void close_conn(bool real_close = true);
    void process();
    bool read_once();
    bool write();
    InetAddress *get_address()
    {
        return &m_address;
    }
    void initmysql_result(connection_pool *connPool);
    int timer_flag;
    int improv;
private:
    InetAddress m_address;
    EventLoop* loop_;
    TcpServer server_;
};
#endif //AYIN_MUDUO_HTTP_CONN_H
