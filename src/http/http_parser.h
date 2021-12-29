//
// Created by ayin on 2021/12/15.
//

#ifndef AYIN_MUDUO_HTTP_PARSER_H
#define AYIN_MUDUO_HTTP_PARSER_H
#include "http_type.h"
#include "muduo/net/Buffer.h"
#include "assert.h"
#include "muduo/base/Logging.h"
namespace http {
using namespace muduo;
using namespace muduo::net;
using handler_ptr = std::shared_ptr<http_handler>;
using Map = std::unordered_map<string, string>;

method_type get_method_type(string str);

bool is_true_method(method_type type);

class http_parser {
    using handler_ptr = std::shared_ptr<http_handler>;

private:

    enum CHECK_STATE {
        CHECK_STATE_REQUESTLINE = 0,
        CHECK_STATE_HEADER,
        CHECK_STATE_CONTENT
    };
    enum HTTP_CODE {
        NO_REQUEST,
        GET_REQUEST,
        BAD_REQUEST,
        NO_RESOURCE,
        FORBIDDEN_REQUEST,
        FILE_REQUEST,
        INTERNAL_ERROR,
        CLOSED_CONNECTION
    };
    enum LINE_STATUS {
        LINE_OK = 0,
        LINE_BAD,
        LINE_OPEN
    };
private:

    LINE_STATUS parse_line();

    HTTP_CODE parse_request_line(string &rl);

    HTTP_CODE parse_header(string &head);

    HTTP_CODE parse_content(string &head);

    Buffer *buffer_;
    CHECK_STATE m_check_state;
/* # bytes in body (0 if no Content-Length header) */
    handler_ptr hptr_;
    bool m_linger;
public:
    void init();

    HTTP_CODE parse_http(Buffer *buf, handler_ptr hptr);

    Map parse_content(handler_ptr hptr);
};

int find_CRLF(string& str);
void remove_pre_space(string& str);
void remove_post_space(string& str);
}
#endif //AYIN_MUDUO_HTTP_PARSER_H
