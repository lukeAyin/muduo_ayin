//
// Created by ayin on 2021/12/15.
//

#ifndef AYIN_MUDUO_HTTP_PARSER_H
#define AYIN_MUDUO_HTTP_PARSER_H
#include "http_type.h"
namespace http {
    string get_substr(string* str,char de);
    http_handler parse_http(string &str);

}


#endif //AYIN_MUDUO_HTTP_PARSER_H
