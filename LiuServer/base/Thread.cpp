#include"Thread.h"
#include"CurrentThread.h"
#include"sys/types.h"
#include <unistd.h>
#include <sys/types.h>
#include<x86_64-linux-gnu/sys/syscall.h>
#include<stdio.h>
#include<stdint.h>
#include <sys/prctl.h>
#include<assert.h>
#include<functional>
namespace CurrentThread {
	__thread int t_cachedTid = 0;
	__thread char t_tidString[32];
	__thread int t_tidStringLength;
	__thread const char* t_threadName;
}
pid_t gettid() { return static_cast<pid_t>(::syscall(SYS_gettid)); }
void CurrentThread::cacheTid() {
    if (t_cachedTid == 0) {
        t_cachedTid = gettid();
        t_tidStringLength=
        snprintf(t_tidString,sizeof(t_tidString),"%5d ", t_cachedTid);
    }
}

Thread::Thread(const std::string& name)
    :started_(false),
    join_ed(false),
    pthreadId_(0),
    tid_(0),
    name_(name),latch_(1){
    setDefaultName();
 }
Thread::~Thread(){//虚析构函数，无论使用父类指针还是子类指针，都是先析构子类，再析构父类。
     if(started_&&!join_ed&&std_thread_ptr->joinable())//已经开始且没有join,且joinable()=true
        std_thread_ptr->detach();
 }
AtomicInt32 Thread::numCreated_;
void Thread::setDefaultName(){
  int num = numCreated_.incrementAndGet();
  if (name_.empty())
  {
    char buf[32];
    snprintf(buf, sizeof buf, "Thread%d", num);
    name_ = buf;
  }
}
void Thread::startInNewThread(){
    tid_=CurrentThread::tid();
    latch_.countdown();
    CurrentThread::t_threadName=name_.empty()?"Thread":name_.c_str();
    //Linux下线程重命名的方法
    prctl(PR_SET_NAME,CurrentThread::t_threadName);
    //printf("create %d,%s\n",tid_,name_.c_str());
    runInThisThread();
    //printf("finish %d,%s,%s\n",tid_,name_.c_str(),CurrentThread::t_threadName);
    CurrentThread::t_threadName="funished";
}
void Thread::start(){
    assert(!started_);
    started_=true;
    std_thread_ptr.reset( new std::thread(std::bind(&Thread::startInNewThread,this)));
    latch_.wait();
    assert(tid_ > 0);
}
void Thread::join(){
    assert(started_);
    assert(!this->join_ed);
    assert(std_thread_ptr->joinable());//未被结合或者分离的非空任务线程会返回true, 否则返回false。
    join_ed=true;
    std_thread_ptr->join();
}