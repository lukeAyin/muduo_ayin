//
// Created by ayin on 2021/12/15.
//

#include <iostream>
#include <utility>
#include "http_parser.h"
namespace http{
method_type get_method_type(string str){
    transform(str.begin(), str.end(),str.begin(), tolower);
    if(str=="get"){
        method_type res(method_type::GET);
        return res;
    }else if(str=="post"){
        method_type res(method_type::POST);
        return res;
    }else if(str=="put"){
        method_type res(method_type::PUT);
        return res;
    }else if(str=="delete"){
        method_type res(method_type::DELETE);
        return  res;
    }
    method_type res(method_type::ERROR);
    return res;
}
bool is_true_method(method_type type){
    return true;
}
//以分隔符de来，得到子字符串，会忽视字符串最前端的分隔符，如果没有子字符串会返回nullptr;
string get_substr(string& str,char de){
    int id=0;
    for(;id<str.size();++id){
        if(str[id]!=de){
            break;
        }
    }
    int ed=id;
    for(;ed<str.size();++ed){
        if(str[ed]==de){
            break;
        }
    }
    string res=str.substr(id,ed-id);
    str=str.substr(std::min(ed+1,(int)str.size()));
    return res;
}
int find_CRLF(string& str){
    return str.find("\r\n");
}
void remove_pre_space(string& str){
    str.erase(0,str.find_first_not_of(" "));
}
void remove_post_space(string& str){
    str.erase(str.find_last_not_of(" "));
}
//解析整个http请求报文
http_parser::HTTP_CODE http_parser::parse_http(Buffer *buf,handler_ptr hptr){
    hptr_=std::move(hptr);
    HTTP_CODE ret=NO_REQUEST;
    LINE_STATUS line_status=LINE_OK;
    switch(m_check_state)
    {
        case CHECK_STATE_REQUESTLINE:
        {
            assert(m_check_state==CHECK_STATE_REQUESTLINE);
            const char* crlf=buf->findCRLF();
            if(crlf){
                string request_line(buf->peek(),crlf);
                LOG_INFO<<"request_line:"<<request_line;
                ret= parse_request_line(request_line);
                if(ret==GET_REQUEST){
                    m_check_state=CHECK_STATE_HEADER;
                }else{
                    return ret;
                }
                buf->retrieveUntil(crlf+2);
            }else{
                LOG_ERROR<<"REQUESTLINE ERROR!\n";
                return BAD_REQUEST;
            }
            if(buf->readableBytes()&&m_check_state==CHECK_STATE_HEADER){

            }else{
                break;
            }
        }
        case CHECK_STATE_HEADER:
        {
            assert(m_check_state==CHECK_STATE_HEADER);
            while(buf->readableBytes()&&m_check_state==CHECK_STATE_HEADER) {
                const char *crlf = buf->findCRLF();
                if (crlf) {
                    string header(buf->peek(), crlf);
                    if (!header.empty()) {
                        ret = parse_header(header);
                    } else if (hptr_->content_length != 0) {
                        m_check_state = CHECK_STATE_CONTENT;
                        LOG_INFO << "Has Content";
                    }
                    buf->retrieveUntil(crlf + 2);
                } else {
                    LOG_WARN << "parse header no crlf";
                    return BAD_REQUEST;
                }
            }
            if(buf->readableBytes()&&m_check_state==CHECK_STATE_CONTENT){

            }else{
                break;
            }
        }
        case CHECK_STATE_CONTENT:
        {
            assert(m_check_state==CHECK_STATE_CONTENT);
            if(!hptr_->is_got_content() && buf->readableBytes()){
                size_t len=std::min(buf->readableBytes(),
                                    hptr_->content_length - hptr_->has_read_content);
                assert(len>0);
                hptr_->content_.append(buf->peek(), len);
                buf->retrieve(len);
                hptr_->has_read_content+=len;
                LOG_INFO<<"content_add_len:"<<len;
                if(hptr_->is_got_content()){
                    LOG_INFO<<"http content:"<<hptr_->content_;
                    m_check_state=CHECK_STATE_REQUESTLINE;
                }
            }else{
                LOG_ERROR<<"content_error!";
                return INTERNAL_ERROR;
            }
            break;
        }
        default:
        {
            return  INTERNAL_ERROR;
        }
    }
    return GET_REQUEST;
}
//

//解析http请求行
http_parser::HTTP_CODE http_parser::parse_request_line(string& rl){
    string method_str= get_substr(rl,' ');
        hptr_->method_= get_method_type(method_str);
    if(!is_true_method(hptr_->method_)){
        return BAD_REQUEST;
    }
        hptr_->URI_= get_substr(rl, ' ');
    LOG_INFO << "method_type:" << method_str << " URI:" << hptr_->URI_;
    return GET_REQUEST;
}


http_parser::HTTP_CODE http_parser::parse_header(string &head) {
    std::transform(head.begin(),head.end(),head.begin(), tolower);
    string key= get_substr(head,':');
    string value=head;
    if(key=="content-length"){
        hptr_->content_length= std::stoull(value);
        LOG_INFO<<"content-length:"<<value;
    }else if(key=="connection"){
        if(value=="keep-alive"){
            m_linger=true;
        }
        LOG_INFO<<"keep-alive:"<<m_linger;
    }else if(key=="content-type"){
        LOG_INFO<<"content-type:"<<value;
        string type= get_substr(value,';');
        remove_pre_space(type);
        if(type=="multipart/form-data"){
            hptr_->content_type=http_handler::MUTIPART_FORM_DATA;
            string tmp= get_substr(value,'=');
            remove_pre_space(tmp);
            assert(tmp=="boundary");
            hptr_->boundary="--"+value;
        }else{
            LOG_WARN<<"content-type:"<<type;
        }
    }else{
        LOG_WARN<<"unknown header:"<<key;
    }
    return GET_REQUEST;
}

void http_parser::init() {
    m_check_state=CHECK_STATE_REQUESTLINE;
    m_linger=false;
}

Map http_parser::parse_content(handler_ptr hptr) {
    Map cmap;
    if(hptr->content_length==0){
        return cmap;
    }
    if(hptr->content_type==http_handler::MUTIPART_FORM_DATA){
        assert(hptr->boundary.size()!=0);

        string boundary=hptr->boundary;
        int b_length=boundary.size();
        assert(hptr->content_.find(boundary)==0);
        int pos=b_length;
        int l_pos=b_length;
        while((pos=hptr->content_.find(boundary,pos+1))!=string::npos){
            string str=hptr->content_.substr(l_pos,pos-l_pos);
            l_pos=pos+b_length;
            assert(str.find("Content-Disposition: form-data;")==2);
            int st=str.find("\"")+1;
            int ed=str.find("\"",st);
            string key=str.substr(st,ed-st);
            int crlf= str.find("\r\n\r\n");
            string value=str.substr(crlf+4);
            cmap[key]=value;
            LOG_INFO<<"content-key:"<<key<<"||content-value:"<<value;
        }
    }
    LOG_WARN<<"content_type:"<<hptr->content_type;
    return cmap;
}
}