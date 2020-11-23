#include "EventLoop.h"
#include "Thread.h"
#include"Test.h"
#include<string>
EventLoop* g_loop;
class ThreadTest2:public Thread
{
 public:
    ThreadTest2(std::string name=std::string())
    :Thread(name)
  {
  }
  void runInThisThread();
};
void ThreadTest2::runInThisThread()
{
  g_loop->loop();
}
int EventLoop_Poller_channel_test2_main()
{
  EventLoop loop;
  g_loop = &loop;
  ThreadTest2 thread;
  thread.start();
}