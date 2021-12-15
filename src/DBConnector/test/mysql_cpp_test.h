//
// Created by ayin on 2021/11/24.
//

#ifndef AYIN_MUDUO_MYSQL_CPP_TEST_H
#define AYIN_MUDUO_MYSQL_CPP_TEST_H
#include <mysql++/mysql++.h>
#include <string>
#include <stdio.h>
class Connector {
private:
    mysqlpp::Connection conn;
    using string=std::string;
    const char *const host="localhost";
    const char *const user="ayin";
    const char *const psw="ayin";
    const char *const db="test";
    const unsigned int port=3306;
public:
    bool ConnectDatabase();
    bool  QueryDatabase();
    Connector() noexcept;

};


#endif //AYIN_MUDUO_MYSQL_CPP_TEST_H
