#include "Server.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <functional>
#include "Util.h"
#include "Logging.h"
#include"Server.h"
#include"AcceptChannnel.h"
#include"Singleton.h"
#include"WorkThreadPool.h"
#include"SqlConnPool.h"
//一开始进行调试时发现，不知为何，此时listenFd仍然是0；查资料得知，
//成员对象初始化的次序完全不受它们在初始化表中次序的影响，只由成员对象在类中声明的次序决定。
Server::Server(EventLoop *loop, int connthreadNum, int port,int workthreadNum,int mysqlconnnum)
    : port_(port),
      loop_(loop),
      connthreadNum_(connthreadNum),
      workthreadNum_(workthreadNum),
      mysqlconnnum_(mysqlconnnum),
      connThreadPool_(new ConnThreadPool(loop_, connthreadNum)),
      started_(false),
      listenFd_(socket_bind_listen(port_)),
      acceptChannel_(new AcceptChannel(loop_,connThreadPool_.get(),listenFd_))
{
  //handle_for_sigpipe();
  if (setSocketNonBlocking(listenFd_) < 0) {
    perror("set socket non block failed");
    abort();
  }
}
void Server::start() {
  connThreadPool_->start();
  Singleton<SqlConnPool>::instance().start(
    "localhost","root","124930","LiuServer",0,mysqlconnnum_, 0);
  Singleton<WorkThreadPool>::instance().start(workthreadNum_);
  loop_->addToPoller(acceptChannel_);
  loop_->loop();
  started_ = true;
}