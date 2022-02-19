//
// Created by ayin on 2021/12/18.
//
#include "muduo/base/Logging.h"
#include "muduo/base/Thread.h"
#include "muduo/net/TcpClient.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/EventLoopThreadPool.h"

#include <unistd.h>
#include <stdio.h>
#include <utility>
using namespace muduo;
using namespace muduo::net;
string test_get1="GET http_url HTTP\\1.1\r\nContent-length:10\r\n\r\nThisisten!\r\n";
class Test_Client;
class Session:noncopyable{
public:
    Session(EventLoop* loop,
            const InetAddress& serverAddr,
            const string& name,
            Test_Client* owner)
            : client_(loop,serverAddr,name),
            owner_(owner),
            bytesRead_(0),
            bytesWritten_(0),
            messagesRead_(0)
    {
        client_.setConnectionCallback(
                std::bind(&Session::onConnection, this, _1));
        client_.setMessageCallback(
                std::bind(&Session::onMessage, this, _1, _2, _3));
    }
    void start(){
        client_.connect();
    }
    void stop(){
        client_.disconnect();
    }
private:
    void onConnection(const TcpConnectionPtr& conn){
        LOG_INFO<<"send message";
        if (conn->connected())
        {
            conn->setTcpNoDelay(true);
            conn->send(test_get1);
            LOG_INFO<<"connected.";
        }
        else
        {
            LOG_WARN<<"not connected.";
        }
    };
    void onMessage(const TcpConnectionPtr& conn,Buffer* buf,Timestamp){
        ++messagesRead_;
        bytesRead_ += buf->readableBytes();
        bytesWritten_ += buf->readableBytes();
        conn->send(buf);
    };
    TcpClient client_;
    Test_Client* owner_;
    int64_t bytesRead_;
    int64_t bytesWritten_;
    int64_t messagesRead_;
};
class Test_Client:noncopyable{
public:
    Test_Client(EventLoop* loop,
           const InetAddress& serverAddr,
           int blockSize,
           int sessionCount,
           int timeout,
           int threadCount)
            : loop_(loop),
              threadPool_(loop, "pingpong-client"),
              sessionCount_(sessionCount),
              timeout_(timeout)
    {
        loop->runAfter(timeout, std::bind(&Test_Client::handleTimeout, this));
        if (threadCount > 1)
        {
            threadPool_.setThreadNum(threadCount);
        }
        threadPool_.start();

        for (int i = 0; i < blockSize; ++i)
        {
            message_.push_back(static_cast<char>(i % 128));
        }

        for (int i = 0; i < sessionCount; ++i)
        {
            char buf[32];
            snprintf(buf, sizeof buf, "C%05d", i);
            Session* session = new Session(threadPool_.getNextLoop(), serverAddr, buf, this);
            session->start();
            sessions_.emplace_back(session);
        }
    }
private:
    void handleTimeout()
    {
        LOG_WARN << "stop";
        for (auto& session : sessions_)
        {
            session->stop();
        }
    }
    EventLoop* loop_;
    EventLoopThreadPool threadPool_;
    int sessionCount_;
    int timeout_;
    std::vector<std::unique_ptr<Session>> sessions_;
    string message_;
    AtomicInt32 numConnected_;
};
int main(int argc,char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: client <host_ip> <port> <threads> <blocksize> ");
        fprintf(stderr, "<sessions> <time>\n");
    } else {
        LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
        Logger::setLogLevel(Logger::INFO);

        const char *ip = argv[1];
        uint16_t port = static_cast<uint16_t>(atoi(argv[2]));
//        int threadCount = atoi(argv[3]);
//        int blockSize = atoi(argv[4]);
//        int sessionCount = atoi(argv[5]);
//        int timeout = atoi(argv[6]);
        EventLoop loop;
        InetAddress serverAddr(ip, port);
        Session session(&loop,serverAddr,"test_parser", nullptr);
        //Test_Client client(&loop, serverAddr, blockSize, sessionCount, timeout, threadCount);
        session.start();
        loop.loop();
        //session.stop();
    }
}