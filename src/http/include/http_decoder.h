//
// Created by 34649 on 2022/3/1.
//

#ifndef AYIN_MUDUO_HTTP_DECODER_H
#define AYIN_MUDUO_HTTP_DECODER_H
#include "http_type.h"
namespace http{
    class decoder{
    public:
        bool read_questLine();
    private:
        string src;
        string _url;
        HTTP_VERSION _httpVersion;
        METHOD _method;
        hmap _map;
    };
}
#endif //AYIN_MUDUO_HTTP_DECODER_H
