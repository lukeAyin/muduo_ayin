//
// Created by ayin on 2021/12/17.
//

#include <iostream>
#include "http_server.h"

void http_server::onConnection(const TcpConnectionPtr &conn) {
    parser.init();
    h_ptr = std::make_shared<handler>();
    LOG_INFO<<"new session connected!";
}

void http_server::onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp receiveTime) {
    LOG_INFO<<"new message!\n";
    LOG_INFO<<string(buf->peek(),buf->readableBytes());
    parser.parse_http(buf,h_ptr);
    parser.parse_content(h_ptr);
    string login="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length:";
    const char* login_path="./static/login.html";
    string tmp;
    size_t file_tmp=FileIO::read_whole_file(login_path,&tmp);
    login+= std::to_string(tmp.size());
    login+="\r\n\r\n";
    login+=tmp;
    conn->send(login);
}

http_server::http_server(EventLoop *loop, const InetAddress &listenAddr)
    : loop_(loop),
      server_(loop, listenAddr, "Http_Server")
{
    server_.setConnectionCallback(
            std::bind(&http_server::onConnection,this,_1));
    server_.setMessageCallback(
            std::bind(&http_server::onMessage,this,_1,_2,_3));
}

void http_server::start() {
    server_.start();
}



