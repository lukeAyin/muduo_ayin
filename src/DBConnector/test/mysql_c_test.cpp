//
// Created by ayin on 2021/11/22.
//
#include "mysql/mysql.h"
#include <stdio.h>
#include <cstring>
MYSQL mysql;
bool ConnectDatabase(){
    mysql_init(&mysql);
    const char host[]="localhost";
    const char user[]="root";
    const char psw[]="root";
    const char table[]="webDB";
    const int port=3306;
    if(!mysql_real_connect(&mysql,host,user,psw,table,port,NULL,0))
    {
        printf("Error connecting to database:%s\n",
               mysql_error(&mysql));
        return false;
    }else{
        printf("Connected...\n");
        return true;
    }
}
bool QueryDatabase()
{
    char query[150];
    strcpy(query,"select * from user");
    mysql_query(&mysql,"set names gbk");
    if(mysql_query(&mysql,query))
    {
        printf("Query failed (%s)\n", mysql_error(&mysql));
        return false;
    }else{
        printf("query success\n");
    }
    MYSQL_RES *res;
    if(!(res= mysql_store_result(&mysql)))
    {
        printf("Couldn't get result from %s\n",
               mysql_error(&mysql));
        return false;
    }
    printf("number of dataline returned:%d\n", mysql_affected_rows(&mysql));
    char *str_field[32];
    for(int i=0;i<4;++i)
    {
        str_field[i]= mysql_fetch_field(res)->name;
    }
    for(int i=0;i<4;++i)
    {
        printf("%10s\t",str_field[i]);
    }
    printf("\n");
    MYSQL_ROW  column;
    while(column= mysql_fetch_row(res))
    {
        printf("%10s\t%10s\t%10s\t%10s\n",column[0],column[1],column[2],column[3]);
    }
    return true;
}
int main(){
    ConnectDatabase();
    QueryDatabase();
};