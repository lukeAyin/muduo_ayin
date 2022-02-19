//
// Created by ayin on 2021/12/27.
//

#include "http_response.h"
using namespace http;

response_handler::response_handler()
:http_type("HTTP/1.1"),
state_code(200)
{}

response_handler::~response_handler() {

}

string http::response(std::shared_ptr<response_handler> rh, std::shared_ptr<http_handler> qh) {
    switch (qh->method_.type) {
        case http::method_type::GET:
            return get_method_response(rh,qh);
        case http::method_type::POST:
            return post_method_response(rh,qh);
        case http::method_type::PUT:
            return put_method_response(rh,qh);
        case http::method_type::DELETE:
            return delete_method_response(rh,qh);
    }
}

string http::get_method_response(std::shared_ptr<response_handler> rh, std::shared_ptr<http_handler> qh) {
    string url=qh->URI_;

    
}
string http::post_method_response(std::shared_ptr<response_handler> rh, std::shared_ptr<http_handler> qh) {

}
string http::put_method_response(std::shared_ptr<response_handler> rh, std::shared_ptr<http_handler> qh) {

}
string http::delete_method_response(std::shared_ptr<response_handler> rh, std::shared_ptr<http_handler> qh) {

}
