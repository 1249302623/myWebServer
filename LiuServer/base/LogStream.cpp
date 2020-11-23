#include"LogStream.h"
#include<algorithm>

const char digits[]="0123456789";
template<class T>
size_t convert(char buf[],T value){
    T i=value;
    char *p=buf;

    do{
        int lsd=static_cast<int>(i%10);
        i/=10;
        *p++=digits[lsd];
    }while (i!=0);

    if(value<0)
        *p++='-';
    *p='\0';
    std::reverse(buf,p);
    
    return p-buf;
}

template<typename T>
void LogStream::formatInteger(T v){
    if(this->buffer_.avail()>=kMaxNumericSize){
        size_t len=convert(buffer_.current(),v);
        buffer_.add(len);
    }
}

LogStream& LogStream:: operator<<(short v){
    *this<<static_cast<int>(v);
    return *this;
}
LogStream& LogStream:: operator<<(unsigned short v){
    *this<<static_cast<unsigned int>(v);
    return *this;
}
LogStream& LogStream::operator<<(int v){
    formatInteger(v);
    return *this;
}
LogStream& LogStream::operator<<(unsigned int v){
    formatInteger(v);
    return *this;
}
LogStream& LogStream::operator<<(long v){
    formatInteger(v);
    return *this;
}
LogStream& LogStream::operator<<(unsigned long v){
    formatInteger(v);
    return *this;
}
LogStream& LogStream::operator<<(long long v){
    formatInteger(v);
    return *this;
}
LogStream& LogStream::operator<<(unsigned long long v){
    formatInteger(v);
    return *this;
}
// LogStream& LogStream::operator<<(const void*){

// }
LogStream& LogStream::operator<<(double v){
    if(this->buffer_.avail()>=this->kMaxNumericSize){
        int len=snprintf(buffer_.current(),kMaxNumericSize,"%.12g",v);
        buffer_.add(len);
    }
    return *this;
}

LogStream& LogStream::operator<<(long double v) {
  if (buffer_.avail() >= kMaxNumericSize) {
    int len = snprintf(buffer_.current(), kMaxNumericSize, "%.12Lg", v);
    buffer_.add(len);
  }
  return *this;
}