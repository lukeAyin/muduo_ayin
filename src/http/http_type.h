//
// Created by ayin on 2021/12/15.
//

#ifndef AYIN_MUDUO_HTTP_TYPE_H
#define AYIN_MUDUO_HTTP_TYPE_H
#include <string>
#include <algorithm>
//#include <cctype>
namespace http{
using string=std::string;
class method_type{

};
class method_get:public method_type{

};
class method_post:public method_type{

};
class method_put:public method_type{

};
class method_delete:public method_type{

};
class method_error:public method_type{

};
method_type get_method_type(string str){
    transform(str.begin(), str.end(),str.begin(), tolower);
    if(str=="get"){
        method_get res;
        return res;
    }
    if(str=="post"){
        method_post res;
        return res;
    }
    if(str=="put"){
        method_post res;
        return res;
    }
    if(str=="delete"){
        method_delete res;
        return res;
    }
    method_error res;
    return res;
}
class http_handler
}
#endif //AYIN_MUDUO_HTTP_TYPE_H
