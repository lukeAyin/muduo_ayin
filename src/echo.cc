#include"muduo/net/TcpServer.h"
#include"muduo/net/EventLoop.h"
#include <iostream>
#ifndef ECHO_H
#define ECHO_H
using namespace muduo::net;
using namespace muduo;

class EchoServer
{
private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);
    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                   muduo::net::Buffer* buf,
                   muduo::Timestamp time);
    muduo::net::EventLoop* loop_;
    muduo::net::TcpServer server_;

public:
    EchoServer(muduo::net::EventLoop* loop,
            const muduo::net::InetAddress& listenAddr);
    void start();
};
void EchoServer::onConnection(const muduo::net::TcpConnectionPtr& conn){
    std::cout<<"connected!!!";
}
void EchoServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                      muduo::net::Buffer* buf,
                      muduo::Timestamp time)
{
    muduo::string msg(buf->retrieveAllAsString());
    std::cout<<msg;
    conn->send(msg);
}
EchoServer::EchoServer(muduo::net::EventLoop* loop,
                       const muduo::net::InetAddress& listenAddr)
    :loop_(loop),
    server_(loop,listenAddr,"EchoServer")
{
    server_.setConnectionCallback(
            std::bind(&EchoServer::onConnection,this,_1));
    server_.setMessageCallback(
            std::bind(&EchoServer::onMessage,this,_1,_2,_3));
}
void EchoServer::start()
{
    server_.start();
}
int main(int argc,char* argv[])
{
        EventLoop loop;
        InetAddress listenAddr(2007);
        EchoServer server(&loop,listenAddr);
        server.start();
        loop.loop();

}

#endif /* ECHO_H */

