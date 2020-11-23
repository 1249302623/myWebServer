#pragma once
#include"Thread.h"
class ThreadTest:public Thread
{
 public:
    ThreadTest(std::string name=std::string())
    :Thread(name)
  {
  }
  void runInThisThread();
};
int Timestamp_test_main();//
int Atomic_test_main();//
int Thread_test_main();//
int LogFile_test_main();//
int BlockingQuene_test_main();//
int BoundedBlockingQuene_test_main();//
int ThreadPool_test_main();//
int Single_test_main();//
int ThreadLocal_test_main();//
int ThreadLocalSingle_test_main();//
int EventLoop_Poller_channel_test1_main();//
int EventLoop_Poller_channel_test2_main();//
int EventLoop_Poller_channel_test3_main();//
int Reactor_test_main();//
int EvThread_test_main();//
int ELThreadPool_test_main();
void Buffer_test_main();
void fun();
void sqlPoolTest();
