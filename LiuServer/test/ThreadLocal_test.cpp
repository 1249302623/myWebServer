#include <ThreadLocal.h>
#include <CurrentThread.h>
#include <Thread.h>

#include <stdio.h>
#include"Test.h"
class Test
{
public:
  Test(){
    printf("tid=%d, constructing %p\n",CurrentThread::tid(), this);
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

ThreadLocal<Test> testObj1;
ThreadLocal<Test> testObj2;

void print()
{
  printf("tid=%d, obj1 %p name=%s\n",
     CurrentThread::tid(),
	 &testObj1.value(),
     testObj1.value().name().c_str());
  printf("tid=%d, obj2 %p name=%s\n",
     CurrentThread::tid(),
	 &testObj2.value(),
     testObj2.value().name().c_str());
}
class ThreadLocal_test:public Thread
{
public:
    ThreadLocal_test(std::string name_):Thread(name_){}
    void runInThisThread()
    {
      print();
      testObj1.value().setName("changed 1");
      testObj2.value().setName("changed 42");
      print();
    }

};



int ThreadLocal_test_main()
{
  testObj1.value().setName("main one");
  print();
  ThreadLocal_test t1("test");
  t1.start();
  t1.join();
  testObj2.value().setName("main two");
  print();

  pthread_exit(0);
}