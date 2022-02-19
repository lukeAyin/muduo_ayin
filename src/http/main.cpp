//
// Created by ayin on 2021/12/17.
//
#include "http_server.h"
int main(){
    EventLoop loop;
    InetAddress listenAddr("127.0.0.1",2007);
    http_server server(&loop,listenAddr);
    Logger::setLogLevel(muduo::Logger::INFO);
    server.start();
    loop.loop();
    return 0;
}