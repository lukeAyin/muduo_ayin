//
// Created by 34649 on 2022/3/1.
//

#ifndef AYIN_MUDUO_HTTP_SERVER_H
#define AYIN_MUDUO_HTTP_SERVER_H
#include"muduo/net/TcpServer.h"
#include"muduo/net/EventLoop.h"
#include "iostream"
#include "http_conn.h"
using namespace muduo::net;
using namespace muduo;
namespace http{
    class http_server{
    public:
        http_server(EventLoop* loop,const InetAddress& listenAddr);
        void start();
    private:
        void onConnection(const TcpConnectionPtr& conn);
        void onMessage(const TcpConnectionPtr& conn,Buffer* buf,Timestamp time);
        EventLoop* loop_;
        TcpServer server_;
    };
}

#endif //AYIN_MUDUO_HTTP_SERVER_H
