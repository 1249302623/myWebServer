#pragma once

#include"LogStream.h"
#include<stdio.h>

class Logger{
private:
    class Imp1{
    public:
        Imp1(const char*fileName,int line);
        void formatTime();

        LogStream stream_;
        int line_;
        std::string basename_;
    };
    Imp1 imp1_;
    std::string info_;
    static std::string logFileName_;
public:
    Logger(const char*file,int line,const std::string info=std::string());
    ~Logger();
    LogStream &stream(){
        return this->imp1_.stream_;
    }
    static void setLogFileName(std::string fileName){
        logFileName_=fileName;
    }
    static std::string getLogFileName(){
        return logFileName_;
    }
};
#define LOG Logger(__FILE__,__LINE__).stream()
#define LOG_INFO Logger(__FILE__,__LINE__,"INFO").stream()
#define LOG_TRACE Logger(__FILE__,__LINE__,"TRACE").stream()
#define LOG_FATAL Logger(__FILE__,__LINE__,"FATAL").stream()
#define LOG_WARN Logger(__FILE__,__LINE__,"WARN").stream()
#define LOG_SYSERR Logger(__FILE__,__LINE__,"SYSERR").stream()
#define LOG_SYSFATAL Logger(__FILE__,__LINE__,"SYSFATAL").stream()
#define LOG_ERROR Logger(__FILE__,__LINE__,"ERROR").stream()
#define LOG_DEBUG Logger(__FILE__,__LINE__,"DEBUG").stream()