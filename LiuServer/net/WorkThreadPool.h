#pragma once

#include"noncopyable.h"
#include<vector>
#include<queue>
#include<functional>
#include<string>
#include"MutexLock.h"
#include"Condition.h"
#include"Thread.h"
#include<memory>
#include"Singleton.h"

class ConnChannel;
class WorkThread:public Thread{
    public:
        WorkThread(std::string name="work")
            :Thread(name)
        {
        }
        void runInThisThread();
        void work();
    private:
        ConnChannel*nowDealConn;

};
class WorkThreadPool:noncopyable{  //线程池是一个单例模式
public:
    explicit WorkThreadPool(const std::string& name="workThread");
    ~WorkThreadPool();
    void start(int numThreads);
    void stop();
    void getRead(ConnChannel*connChanel);
    ConnChannel* read_a_conn();
    bool running(){
        return running_;
    }
private: 
    mutable MutexLock mutex_;
    Condition cond_;
    std::string name_;
    std::vector<std::shared_ptr<WorkThread>> threads_;
    bool running_;
    std::queue<ConnChannel*> read_quene_;
};

