#include<vector>
#include<thread>
#include<iostream>
#include"Test.h"
#include"Singleton.h"
#include"AsyncLogging.h"
#include<mysql/mysql.h>
#include"EventLoop.h"
#include"Server.h"
using namespace std;
//使用ab压力测试命令  ab -t 60 -n 2000000 -c 20000 -r -k http://127.0.0.1:8080/
int main() {

    Singleton<AsyncLogging>::instance().startLog();
    EventLoop mainLoop;
    int connthreadNum=4,port=8080,workthreadNum=3,mysqlconnnum=5;
    Server myHTTPServer(&mainLoop, connthreadNum, port,workthreadNum,mysqlconnnum);
    myHTTPServer.start();
    //sqlPoolTest();
    //Buffer_test_main();
    //EvThread_test_main();
    //Reactor_test_main();
    //LogFile_test_main();
    //EventLoop_Poller_channel_test1_main();
    //EventLoop_Poller_channel_test3_main();
    //Atomic_test_main();
    //Timestamp_test_main();
    //Mutex_test_main();
    //BlockingQuene_test_main();
    //BoundedBlockingQuene_test_main();
    //Single_test_main();
    //ThreadPool_test_main();
    //ThreadLocal_test_main();
    //ThreadLocalSingle_test_main();
}
//总代码约4000行