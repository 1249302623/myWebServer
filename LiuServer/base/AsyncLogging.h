#pragma once
#include"CountDownLatch.h"
#include"LogStream.h"
#include"MutexLock.h"
#include"Thread.h"
#include"noncopyable.h"
#include<memory>
#include<vector>
#include"Timestamp.h"
#include"Logging.h"
class AsyncLogging: public Thread
{
private:   
    //kSmallBuffer = 4000;
    //kLargeBuffer = 4000 * 1000;
    typedef FixedBuffer<kLargeBuffer> Buffer;
    typedef std::vector<std::shared_ptr<Buffer>> BufferVector;
    typedef std::shared_ptr<Buffer> BufferPtr;
    const int fulshInterval_;
    bool running_;
    std::string basename_;
    MutexLock mutex_;
    Condition cond_;
    BufferPtr currentBuffer_;
    BufferPtr nextBuffer_;
    BufferVector buffers_;
public:
    AsyncLogging(const std::string basename=Logger::getLogFileName(),int flushInterval=2);
    ~AsyncLogging(){
        if(running_){
            stopLog();
        }
    }
    void runInThisThread();

    void append(const char* logline,int len);    
    void startLog(){
        running_=true;
        this->start();
    }
    void stopLog(){
        running_=false;
        cond_.notify();
        this->join();
    }

};