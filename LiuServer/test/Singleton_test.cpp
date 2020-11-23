#include <stdio.h>
#include"Singleton.h"
#include"Thread.h"
#include"CurrentThread.h"
#include"Test.h"
class Test
{
public:
  Test()
  {
    printf("tid=%d, constructing %p\n",CurrentThread::tid(), this);
  }

  ~Test()
  {
    printf("tid=%d, destructing %p %s\n", CurrentThread::tid(), this, name_.c_str());
  }

  const std::string& name() const { return name_; }
  void setName(const std::string& n) { 
      name_ = n; 
      printf("tid=%d, %p nameChange=%s\n",CurrentThread::tid(), this, name_.c_str());
}
private:
  std::string name_;
};

class ThreadTest1:public Thread{
  void runInThisThread()
  {
    printf("tid=%d, %p name=%s\n",
          CurrentThread::tid(),
          &Singleton<Test>::instance(),
          Singleton<Test>::instance().name().c_str());
          Singleton<Test>::instance().setName("only one, changed");
  }
};
int Single_test_main()
{
  Singleton<Test>::instance().setName("only one");
  ThreadTest1 t1;
  t1.start();
  t1.join();
  printf("tid=%d, %p name=%s\n",
         CurrentThread::tid(),
         &Singleton<Test>::instance(),
         Singleton<Test>::instance().name().c_str());
}