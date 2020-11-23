#include"Logging.h"
#include<iostream>
#include"Thread.h"
#include"AsyncLogging.h"
#include"Timestamp.h"
#include<memory>
#include"Singleton.h"

std::string Logger::logFileName_ = "./WebServer.log";

Logger::Imp1::Imp1(const char*fileName,int line)
    :stream_(),
     line_(line),
     basename_(fileName)
{
    formatTime();
}

void Logger::Imp1::formatTime(){
    std::string str_t=Timestamp::now().toFormattedString(true);
    this->stream_<<str_t;
}
Logger::Logger(const char*file,int line,const std::string info)
    :imp1_(file,line),info_(info)
{
    imp1_.stream_<<'|'<<this->info_<<'|';
}
Logger::~Logger(){
    //std::cout<<"yes 析构"<<std::endl;
    imp1_.stream_<<"--"<<imp1_.basename_<<':'<<imp1_.line_<<'\n';
    const LogStream::Buffer&  buf(stream().buffer());//一块小buffer
    Singleton<AsyncLogging>::instance().append(buf.data(),buf.length()); 
}


