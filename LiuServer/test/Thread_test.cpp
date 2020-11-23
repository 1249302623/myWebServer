#include"Thread.h"
#include"Condition.h"
#include"CurrentThread.h"
#include<unistd.h>

class Foo:public Thread
{
 public:
 
  explicit Foo(double x)
    : x_(x)
  {
  }
  Foo(double x,std::string name)
    : x_(x),Thread(name)
  {
  }
  void runInThisThread(){
    memberFunc();
  }
  void memberFunc()
  {
    printf("tid=%d, Foo::x_=%f\n", CurrentThread::tid(), x_);
  }

  void memberFunc2(const std::string& text)
  {
    printf("tid=%d, Foo::x_=%f, text=%s\n",CurrentThread::tid(), x_, text.c_str());
  }

 private:
  double x_;
};

int Thread_test_main()
{
  printf("pid=%d, tid=%d\n", ::getpid(),CurrentThread::tid());

  Foo foo(87.53,"thread for member function without argument");
  foo.start();
  foo.join();

  Thread* t4=new Foo(66);
  t4->start();
  t4->join();

  printf("number of created threads %d\n", Thread::numCreated());

  return 0;
}