//
// Created by 34649 on 2022/3/1.
//
#include "include/http_server.h"

http::http_server::http_server(EventLoop *loop, const InetAddress &listenAddr)
:loop_(loop),
 server_(loop,listenAddr,"http_server"){
    server_.setConnectionCallback(std::bind(&http_server::onConnection, this,_1));
    server_.setMessageCallback(std::bind(&http_server::onMessage,this,_1,_2,_3));
}

void http::http_server::start() {
    server_.start();
}

void http::http_server::onConnection(const TcpConnectionPtr &conn) {
    std::cout<<"connected!!!";
}

void http::http_server::onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp time) {
    string msg(buf->retrieveAllAsString());
    std::cout<<msg;
    conn->send(msg);
}
