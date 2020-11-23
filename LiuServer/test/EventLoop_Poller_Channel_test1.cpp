#include "EventLoop.h"
#include "Thread.h"
#include"CurrentThread.h"
#include <stdio.h>
#include"Logging.h"
#include"Test.h"

void ThreadTest::runInThisThread()
{
  printf("threadFunc(): pid = %d, tid = %d\n",
         getpid(),CurrentThread::tid());
  EventLoop loops;
  loops.loop();
}

int EventLoop_Poller_channel_test1_main()
{
  printf("main(): pid = %d, tid = %d\n",
         getpid(), CurrentThread::tid());

  EventLoop loop;
  ThreadTest thread;
  thread.start();

  loop.loop();

}