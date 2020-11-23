#include <ThreadLocalSingleton.h>
#include <CurrentThread.h>
#include <Thread.h>
#include"Test.h"
#include <stdio.h>
#include<unistd.h>

class Test
{
 public:
  Test()
  {
    printf("tid=%d, constructing %p\n", CurrentThread::tid(), this);
  }

  ~Test()
  {
    printf("tid=%d, destructing %p %s\n",CurrentThread::tid(), this, name_.c_str());
  }

  const std::string& name() const { return name_; }
  void setName(const std::string& n) { name_ = n; }

 private:
  std::string name_;
};
class threadTest:public Thread{
public:
  threadTest(const char* changeto,std::string name_=std::string()):
      Thread(name_),changeTo(changeto){}
  const char* changeTo;
  void runInThisThread()
  {
    printf("tid=%d, %p name=%s\n",
          CurrentThread::tid(),
          &ThreadLocalSingleton<Test>::instance(),
          ThreadLocalSingleton<Test>::instance().name().c_str());
    ThreadLocalSingleton<Test>::instance().setName(changeTo);
    printf("tid=%d, %p name=%s\n",
          CurrentThread::tid(),
          &ThreadLocalSingleton<Test>::instance(),
          ThreadLocalSingleton<Test>::instance().name().c_str());
    sleep(1);
  }
};
int ThreadLocalSingle_test_main()
{
  ThreadLocalSingleton<Test>::instance().setName("main one");
  threadTest t1("thread1");
  threadTest t2("thread2");
  t1.start();
  t2.start();
  t1.join();
  printf("tid=%d, %p name=%s\n",
         CurrentThread::tid(),
         &ThreadLocalSingleton<Test>::instance(),
         ThreadLocalSingleton<Test>::instance().name().c_str());
  t2.join();

  pthread_exit(0);
}