//
// Created by ayin on 2021/12/17.
//

#ifndef AYIN_MUDUO_HTTP_SERVER_H
#define AYIN_MUDUO_HTTP_SERVER_H
#include "http_parser.h"
#include "muduo/net/TcpServer.h"
#include "io_file.h"
using namespace muduo;
using namespace muduo::net;
using namespace http;
class http_server {
    using handler=http::http_handler;
    using handler_ptr=std::shared_ptr<handler>;
    using Map=std::map<string,string>;
private:
    TcpServer server_;
    EventLoop* loop_;
    http::http_parser parser;
    handler_ptr h_ptr;
    void do_request(handler_ptr hptr){

    }
    Map parser_content(handler_ptr hptr_);

public:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn,
                   Buffer* buf,
                   Timestamp receiveTime);
    http_server(EventLoop* loop,const InetAddress& listenAddr);
    bool hasUser(string user,string password);
    void start();
};


#endif //AYIN_MUDUO_HTTP_SERVER_H
