//
// Created by ayin on 2021/12/27.
//

#ifndef AYIN_MUDUO_HTTP_RESPONSE_H
#define AYIN_MUDUO_HTTP_RESPONSE_H
#include "http_type.h"
#include "io_file.h"

#include <map>
namespace http{
    using ssmap=std::map<string,string>;
class response_handler{
public:
    response_handler();
    ~response_handler();
    enum STATE_CODE{
        STATE_OK=200,
        STATE_NOT_FOUND=404,
        STATE_ERROR=500
    };
    string get_state(){
        switch (state_code) {
            case STATE_OK:
                return "OK";
            case STATE_ERROR:
                return "Internal Server Error";
            case STATE_NOT_FOUND:
                return "Not Found";
        }
        return "Not Found";
    }
    string to_string(){
        string res="";
        res+=http_type;
        res+=" ";
        res+=std::to_string(state_code);
        res+=" ";
        res+=get_state();
        res+=CRLF;
        for(auto [key,value]:header){
            res+=key;
            res+=": ";
            res+=value;
            res+=CRLF;
        }
        res+=CRLF;
        res+=content;
    }
    int state_code;
    string http_type;
    ssmap header;
    string content;
private:
    const string CRLF="\r\n";
};
class http_response {

};
string response(std::shared_ptr<response_handler> rh,std::shared_ptr<http_handler> qh);
string get_method_response(std::shared_ptr<response_handler> rh,std::shared_ptr<http_handler> qh);
string post_method_response(std::shared_ptr<response_handler> rh,std::shared_ptr<http_handler> qh);
string put_method_response(std::shared_ptr<response_handler> rh,std::shared_ptr<http_handler> qh);
string delete_method_response(std::shared_ptr<response_handler> rh,std::shared_ptr<http_handler> qh);
}


#endif //AYIN_MUDUO_HTTP_RESPONSE_H
