//
// Created by ayin on 2021/11/24.
//

#include "mysql_cpp_test.h"

int main(){
    Connector c;
    c.ConnectDatabase();
    c.QueryDatabase();
}

bool Connector::QueryDatabase() {
    mysqlpp::Query query=conn.query("select * from user;");
    if(mysqlpp::StoreQueryResult res=query.store()){
        mysqlpp::StoreQueryResult::const_iterator it;
        for(it=res.begin();it!=res.end();++it){
            mysqlpp::Row row=*it;
            for(const auto& str:row){

                std::cout<<str<<" ";
            }
            printf(" \n");
        }
        return true;
    }else{
        printf("Couldn't get result from db %s\n",query.error());
    }
    return false;
}

bool Connector::ConnectDatabase() {
    if(conn.connect(db,host,user,psw,port)){
        printf("Connected..\n");
        return true;
    }else{
        printf("Error connecting to database!%s\n",conn.error());
    }
    return false;
}

Connector::Connector() noexcept
    :conn(false)
{

}
