//
// Created by ayin on 2021/12/14.
//

#include "http_conn.h"
http_conn::http_conn(EventLoop *loop, const InetAddress &listenAddr)
    :loop_(loop),
     server_(loop,listenAddr,"httpServer")
{

}