#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"
#include <iostream>
#ifndef FINGER_H
#define FINGER_H
using namespace muduo;
using namespace muduo::net;
class Finger
{
private:
    using UserMap=std::map<string,string>;
    UserMap users;
    TcpServer server_;    
    EventLoop* loop_;

public:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn,
                    Buffer* buf,
                    Timestamp receiveTime);
    string getUser(const string& user);
    void insertUser(const string&& user,const string &&message);
    Finger(EventLoop *loop,const InetAddress& listenAddr);
    void start();
};
string Finger::getUser(const string &user)
{
    string res="No such user!";
    UserMap::iterator it=users.find(user);
    if(it!=users.end())
    {
        res=it->second;
    }
    return res;
}
void Finger::insertUser(const string &&user,const string &&message)
{
    users[user]=message;
}
void Finger::onMessage(const TcpConnectionPtr &conn,
                        Buffer *buf, 
                        Timestamp receiveTime)
{
    const char* crlf=buf->findCRLF();
    if(crlf)
    {
        string str(buf->peek(),crlf);
        string user;
        if(str.size()>6&&str.substr(0,6)=="insert"){
            int u_start=6;
            while (u_start<str.size()){
                if(str[u_start]!=' '){
                    break;
                }
                u_start++;
            }
            int u_end=u_start;
            while(u_end<str.size()){
                if(str[u_end]==' '){
                    break;
                }
                u_end++;
            }
            int i_start=u_end;
            while(i_start<str.size()){
                if(str[i_start]!=' '){
                    break;
                }
                i_start++;
            }
            user=str.substr(u_start,u_end-u_start);
            insertUser(str.substr(u_start,u_end-u_start),
                       str.substr(i_start,str.size()-i_start));

        }else{
            user=str;
        }
        conn->send(getUser(user)+"\r\n");
        buf->retrieveUntil(crlf+2);
        //conn->shutdown();
    }
}
void Finger::onConnection(const TcpConnectionPtr &conn) 
{
    std::cout<<"connected!!!";
}
void Finger::start()
{
    server_.start();
}
Finger::Finger(EventLoop* loop,const InetAddress& listenAddr)
    :loop_(loop),
     server_(loop,listenAddr,"FingerServer")
{
    server_.setConnectionCallback(
            std::bind(&Finger::onConnection,this,_1));
    server_.setMessageCallback(
            std::bind(&Finger::onMessage,this,_1,_2,_3));
}
int main()
{
    EventLoop loop;
    InetAddress listenAddr(2007);
    Finger finger(&loop,listenAddr);
    finger.start();
    loop.loop();
    return 0;
}
#endif /* FINGER_H */
