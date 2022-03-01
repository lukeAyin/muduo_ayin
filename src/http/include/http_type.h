//
// Created by 34649 on 2022/3/1.
//

#ifndef AYIN_MUDUO_HTTP_TYPE_H
#define AYIN_MUDUO_HTTP_TYPE_H
#include <string>
#include "map"
namespace http{
    using string=std::string;
    using hmap=std::map<string ,string>;
    enum HTTP_VERSION{
        HTTP_1=0,
        HTTP_11=1,
        HTTP_2,
        HTTP_3
    };
    enum METHOD{
        GET=0,
        POST,
        DELETE,
        PUT,
    };
    enum HTTP_CODE{
        
    };
}


#endif //AYIN_MUDUO_HTTP_TYPE_H
