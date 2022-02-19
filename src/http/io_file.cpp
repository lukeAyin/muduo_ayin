//
// Created by ayin on 2021/12/27.
//

#include "io_file.h"
#include <assert.h>

using namespace http;
FileIO::read_file::read_file(string path)
:fd_(::fopen(path.c_str(),"rt")),
err_(0){
    //assert(content!= nullptr);

    assert(fd_!= nullptr);
    buf_[0]='\0';
    if(fd_== nullptr){
        err_=errno;
    }
}

FileIO::read_file::~read_file() {
    if(fd_!= nullptr){
        fclose(fd_);
    }
}

int FileIO::read_file::readToString(string *content) {
    assert(fd_!= nullptr);
    if(fd_ != nullptr){
        fseek(fd_,0,SEEK_END);
        long lSize= ftell(fd_);
        rewind(fd_);
        assert(buf_!= nullptr);
        size_t result= fread(buf_,1,lSize,fd_);
        assert(result==lSize);
        content->append(buf_);
    }else{
        err_=errno;
    }
    return err_;
}
size_t FileIO::read_whole_file(const char *pathname,string * content) {
    read_file rf(pathname);
    rf.readToString(content);
    return 0;
}


