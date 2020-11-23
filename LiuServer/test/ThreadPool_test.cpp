#include <stdio.h>
#include"ThreadPool.h"
#include"CurrentThread.h"
#include"Test.h"
#include"Logging.h"
#include<unistd.h>
#include<functional>
void print()
{
  printf("tid=%d\n", CurrentThread::tid());
  
  LOG_INFO<<CurrentThread::tid()<<';'<<CurrentThread::name();
}

void printString(const std::string& str)
{
  printf("tid=%d, str=%s\n",CurrentThread::tid(), str.c_str());
  LOG_INFO<<CurrentThread::tid()<<';'<<CurrentThread::name();
  //usleep(1);
}

int ThreadPool_test_main()
{
  printf("tid=%d\n", CurrentThread::tid());
  Singleton<ThreadPool>::instance().start(5);

  Singleton<ThreadPool>::instance().run(print);
  Singleton<ThreadPool>::instance().run(print);
  for (int i = 0; i < 1000; ++i)
  {
    char buf[32];
    snprintf(buf, sizeof buf, "task %d", i);
    Singleton<ThreadPool>::instance().run(std::bind(printString,std::string(buf)));
  }
  sleep(2);
}