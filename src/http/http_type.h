//
// Created by ayin on 2021/12/15.
//

#ifndef AYIN_MUDUO_HTTP_TYPE_H
#define AYIN_MUDUO_HTTP_TYPE_H
#include <string>
#include <algorithm>
#include "muduo/net/EventLoop.h"

//#include <cctype>
namespace http{
const char CR='\r';
const char LF='\n';
using string=std::string;
class method_type{
public:
    enum METHOD{
        GET=0,
        POST,
        PUT,
        DELETE,
        ERROR,
        INIT
    };
    int type;
    method_type(int t):type(t){};
    method_type():type(INIT){};
};


class http_handler{
public:
    enum CONTENT_TYPE{
        UNINIT=0,
        MUTIPART_FORM_DATA=1,
    };
    method_type method_;
    string URI_;
    string content_;
    uint64_t content_length;
    uint64_t has_read_content;
    int content_type;
    string boundary;
    http_handler(method_type m,string u)
    : method_(m), URI_(u)
    {

    };
    http_handler()
        :content_length(0),
        has_read_content(0),
        content_type(UNINIT)
    {

    };
    bool is_got_content(){
        return content_length <= has_read_content;
    }
};

}
#endif //AYIN_MUDUO_HTTP_TYPE_H
