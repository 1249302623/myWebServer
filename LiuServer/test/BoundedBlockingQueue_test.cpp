#include <string>
#include <stdio.h>
#include"Thread.h"
#include"BoundedBlockingQuene.h"
#include"CountDownLatch.h"
#include"Timestamp.h"
#include<memory>
#include<unistd.h>
class Test:public Thread
{
public:
  Test(const std::string& name)
    : Thread(name)
  {}
  static BoundedBlockingQuene<std::string> queue_;
  static std::unique_ptr<CountDownLatch> latch_;
  static std::vector<std::shared_ptr<Thread> > threads_;
  static void run(int times)
  {
    printf("waiting for count down latch\n");
    Test::latch_->wait();
    printf("all threads started\n");
    for (int i = 0; i < times; ++i)
    {
      char buf[32];
      snprintf(buf, sizeof buf, "hello %d", i);
      queue_.put(buf);
      printf("tid=%d, put data = %s, size = %zd |time=%s\n",CurrentThread::tid(), buf, queue_.size(),
        Timestamp::now().toFormattedString().c_str());
    }
  }

  static void joinAll()
  {
    for (size_t i = 0; i < threads_.size(); ++i)
    {
      queue_.put("stop");
    }
    for(std::vector<std::shared_ptr<Thread>>::iterator it=threads_.begin();it!=threads_.end();it++){
        (*it)->join();
    }
  }
  static void InitTest(int numThreads){
    latch_.reset(new CountDownLatch(numThreads));
    threads_.reserve(numThreads);
    for (int i = 0; i < numThreads; ++i)
    {
      char name[32];
      snprintf(name, sizeof name, "work thread %d", i);
      std::shared_ptr<Thread> s(new Test(std::string(name)));
      threads_.push_back(s);
    }
    for(std::vector<std::shared_ptr<Thread>>::iterator it=threads_.begin();it!=threads_.end();it++){
        (*it)->start();
    }
  }
private:
  void runInThisThread()
  {
    printf("tid=%d, %s started\n",
           CurrentThread::tid(),
           CurrentThread::name());
    latch_->countdown();
    bool running = true;
    while (running)
    {
      usleep(100);
      std::string d(queue_.take());
      printf("tid=%d, get data = %s, size = %zd |time=%s\n", CurrentThread::tid(), d.c_str(), queue_.size()
        ,Timestamp::now().toFormattedString().c_str());
      running = (d != "stop");
    }

    printf("tid=%d, %s stopped\n",
           CurrentThread::tid(),
           CurrentThread::name());
  }
};
BoundedBlockingQuene<std::string> Test:: queue_(50);
std::unique_ptr<CountDownLatch> Test:: latch_;
std::vector<std::shared_ptr<Thread> > Test:: threads_;

int BoundedBlockingQuene_test_main()
{
  printf("pid=%d, tid=%d\n", ::getpid(),CurrentThread::tid());
  Test::InitTest(5);
  Test::run(100);
  Test::joinAll();
  printf("number of created threads %d\n",Thread::numCreated());
}