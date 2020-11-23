#include"Test.h"
#include"EventLoop.h"
#include"Server.h"
#include <stdio.h>


int Reactor_test_main()
{
  printf("main(): pid = %d\n", getpid());
  EventLoop mainLoop;
  int threadNum=3,port=8080;
  Server myHTTPServer(&mainLoop, threadNum, port);
  myHTTPServer.start();
}