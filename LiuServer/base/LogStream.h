#pragma once
#include"noncopyable.h"
#include<string>
#include<string.h>
//可变缓冲类
template<int SIZE>
class FixedBuffer:noncopyable{
private:
    char data_[SIZE];
    char* cur_;

    const char* end() const{return data_+sizeof data_;}
public:
    FixedBuffer():cur_(data_){}
    ~FixedBuffer(){}

    void append(const char*buf,size_t len){
        if(this->avail()>static_cast<int>(len)){
            memcpy(cur_,buf,len);
            cur_+=len;
        }
    }
    const char* data() const{return data_;}
    int length() const{return static_cast<int>(cur_-data_);}

    char* current() const{return cur_;}
    int avail() const{return static_cast<int>(end()-cur_);}
    void add(size_t len){cur_+=len;}

    void reset(){
        //this->bzero();
        cur_=data_;
    }
    void bzero(){ memset(data_,0,sizeof(data_)); }
};
const int kSmallBuffer = 4000;
const int kLargeBuffer = 4000 * 1000;
class LogStream:noncopyable{
public:
    typedef FixedBuffer<kSmallBuffer> Buffer;
private:
    template<typename T>
    void formatInteger(T);
    
    Buffer buffer_;

    static const int kMaxNumericSize=32;
public:
    LogStream& operator<<(bool v){
        buffer_.append(v?"1":"0",1);
        return *this;
    }
    
    LogStream& operator<<(short);
    LogStream& operator<<(unsigned short);
    LogStream& operator<<(int);
    LogStream& operator<<(unsigned int);
    LogStream& operator<<(long);
    LogStream& operator<<(unsigned long);
    LogStream& operator<<(long long);
    LogStream& operator<<(unsigned long long);

    //LogStream& operator<<(const void*);

    LogStream& operator<<(float v){
        *this<<static_cast<double>(v);
    }
    LogStream& operator<<(double);
    LogStream& operator<<(long double);

    LogStream& operator<<(char v){
        buffer_.append(&v,1);
        return *this;
    }

    LogStream& operator<<(const char* str){
        if(str)
            buffer_.append(str,strlen(str));
        else
            buffer_.append("(null)",6);
        return *this;
    }
    LogStream& operator<<(const unsigned char* str){
        return operator<<(reinterpret_cast<const char*>(str));
    }

    LogStream& operator<<(const std::string& v){
        buffer_.append(v.c_str(),v.size());
        return *this;
    }

    void append(const char* data,int len){
        buffer_.append(data,len);
    }
    const Buffer& buffer() const{return this->buffer_;}
    void resetBuffer(){buffer_.reset();}
};