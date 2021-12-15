//
// Created by ayin on 2021/12/15.
//

#include "http_parser.h"
namespace http{
    string get_substr(string& str,char de){
        int id=0;
        for(;id<str.size();++id){
            if(str[id]!=de){
                break;
            }
        }
        int ed=id;
        for(;ed<str.size();++ed){
            if(str[id]==de){
                break;
            }
        }
        string res= str.substr(id,ed-id);
        str=str.substr(ed,str.size()-ed);
        return res;
    }
    http_handler parse_http(string& str){
        string method_str= get_substr(str,' ');
        method_type type= get_method_type(method_str);
        string URI= get_substr(str,' ');
        http_handler res(type,URI);
        return res;
    }
}