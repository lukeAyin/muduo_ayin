//
// Created by ayin on 2021/12/27.
//

#ifndef AYIN_MUDUO_IO_FILE_H
#define AYIN_MUDUO_IO_FILE_H

#include <string>
#include <cstdio>
#include "muduo/base/Logging.h"
#include "muduo/base/noncopyable.h"
namespace http{
namespace FileIO{
using string=std::string;
class read_file:muduo::noncopyable{
public:
    read_file(string path);
    ~read_file();

    int readToString(string* content);
    const char* buffer() const{return buf_;}
    static const int kBufferSize=64*1024;
private:
    FILE *fd_;
    int err_;
    char buf_[kBufferSize];
};

size_t read_whole_file(const char *pathname,string* content);
}
}


#endif //AYIN_MUDUO_IO_FILE_H
