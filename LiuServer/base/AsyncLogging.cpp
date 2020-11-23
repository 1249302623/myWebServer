#include"AsyncLogging.h"
#include"LogFile.h"
#include<functional>
#include<assert.h>
#include"Timestamp.h"
AsyncLogging::AsyncLogging(const std::string logFileName_,int flushInterval)
    :fulshInterval_(flushInterval),
     running_(false),
     basename_(logFileName_),
     mutex_(),
     cond_(mutex_),
     currentBuffer_(new Buffer),//智能指针指向大缓冲区
     nextBuffer_(new Buffer),
     buffers_(),//指向buffer的智能指针vector初始化

     Thread(std::string("LoggingThread"))
{
    //printf("asy构造\n");
    assert(logFileName_.size()>1);
    currentBuffer_->bzero();
    nextBuffer_->bzero();
    buffers_.reserve(16);
}

void AsyncLogging::append(const char* logline,int len){
    MutexLockGuard lock(mutex_);
    if(currentBuffer_->avail()>len){   
        currentBuffer_->append(logline,len);
    }
    else{
        buffers_.push_back(currentBuffer_);
        currentBuffer_.reset();
        if(nextBuffer_)
            currentBuffer_=std::move(nextBuffer_);
            //move操作，current指向右值，右值指向空
        else
            currentBuffer_.reset(new Buffer);
        currentBuffer_->append(logline,len);
        cond_.notify();
    }
}
void AsyncLogging::runInThisThread(){
    assert(running_==true);
    latch_.countdown();
    LogFile output(this->basename_);
    BufferPtr newBuffer1(new Buffer);
    BufferPtr newBuffer2(new Buffer);
    newBuffer1->bzero();
    newBuffer2->bzero();
    BufferVector buffersToWrite;
    buffers_.reserve(16);
    while (running_){
        assert(newBuffer1&&newBuffer1->length()==0);
        assert(newBuffer2&&newBuffer2->length()==0);
        assert(buffersToWrite.empty());
        {
            MutexLockGuard lock(mutex_);
            if(buffers_.empty()){
                cond_.waitForSecond(fulshInterval_);//等2s，2s刷新一次
            }
            buffers_.push_back(currentBuffer_);
            currentBuffer_.reset();

            currentBuffer_=std::move(newBuffer1);
            buffersToWrite.swap(buffers_);//交换
            if(!nextBuffer_){
                nextBuffer_=std::move(newBuffer2);
            }
        }

        assert(!buffersToWrite.empty());

        if (buffersToWrite.size() > 25) {
            char buf[256];
            snprintf(buf, sizeof buf, "Dropped log messages at %s, %zd largerbuffers\n",
               Timestamp::now().toFormattedString().c_str(),buffersToWrite.size()-2);
            fputs(buf, stderr);
            output.append(buf, static_cast<int>(strlen(buf)));
            buffersToWrite.erase(buffersToWrite.begin() + 2, buffersToWrite.end());
        }

        for (size_t i = 0; i < buffersToWrite.size(); ++i) {
        // FIXME: use unbuffered stdio FILE ? or use ::writev ?
            output.append(buffersToWrite[i]->data(), buffersToWrite[i]->length());
        }

        if (buffersToWrite.size() > 2) {
        // drop non-bzero-ed buffers, avoid trashing
            buffersToWrite.resize(2);
        }

        if (!newBuffer1) {
            assert(!buffersToWrite.empty());
            newBuffer1 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer1->reset();
        }

        if (!newBuffer2) {
            assert(!buffersToWrite.empty());
            newBuffer2 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer2->reset();
        }

        buffersToWrite.clear();
        output.flush();
    }
    output.flush();
}