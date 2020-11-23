#include <stdio.h>
#include"EventLoop.h"
#include"ConnThread.h"
#include"Test.h"
#include"Timestamp.h"
#include"Logging.h"
void testThread()
{ 
  printf("runInThread(): pid = %d, tid = %d,time=%s\n",
         getpid(), CurrentThread::tid(),Timestamp::now().toFormattedString().c_str());
}

int EvThread_test_main()
{
  printf("main(): pid = %d, tid = %d,time= %s\n",
         getpid(), CurrentThread::tid(),Timestamp::now().toFormattedString().c_str());

  ConnThread loopThread;
  EventLoop* loop = loopThread.startLoop();
  // 异步调用runInThread，即将runInThread添加到loop对象所在IO线程，让该IO线程执行
  loop->runInLoop(testThread);
  sleep(3);
  loop->quit();
  printf("exit main().\n");
}