#pragma once
#include<string>
#include<memory>
#include"MutexLock.h"
#include"FileUtil.h"
class LogFile
{
private:
    void append_unlocked(const char* logline,int len);//无锁方式append
    
    const std::string basename_;
    const int flushEveryN_;

    int count_;
    std::unique_ptr<MutexLock> mutex_;
    std::unique_ptr<AppendFile> file_;
public:
// 每被append flushEveryN次，flush一下，会往文件写，只不过，文件也是带缓冲区的
    LogFile(const std::string& basename,int flushEveryN=1024);
    ~LogFile();

    void append(const char* logline,int len);
    void flush();
    //bool rollFile();

};


 