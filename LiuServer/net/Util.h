#pragma once
#include <cstdlib>
#include <string>
#include <stdio.h>  // snprintf
#include<string.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>
//封装了ET读取数据的方法，但是没有用到
ssize_t readLT(int sockfd, void *buf, size_t count);
ssize_t readvLT(int sockfd, const struct iovec *iov, int iovcnt);
ssize_t writeLT(int sockfd, const void *buf, size_t count);
ssize_t readET(int fd, void *buff, size_t n);
ssize_t readET(int fd, std::string &inBuffer, bool &zero);
ssize_t readET(int fd, std::string &inBuffer);
ssize_t writeET(int fd, void *buff, size_t n);
ssize_t writeET(int fd, std::string &sbuff);
void handle_for_sigpipe();
int setSocketNonBlocking(int fd);
void setSocketNodelay(int fd);
void setSocketNoLinger(int fd);
void shutDownWR(int fd);
int socket_bind_listen(int port);
//对于TCP套接字（默认情况下），当使用 write()/send() 发送数据时：
//　　1) 首先会检查缓冲区，如果缓冲区的可用空间长度小于要发送的数据，那么 write()/send() 会被阻塞（暂停执行），直到缓冲区中的数据被发送到目标机器，腾出足够的空间，才唤醒 write()/send() 函数继续写入数据。
//　　2) 如果TCP协议正在向网络发送数据，那么输出缓冲区会被锁定，不允许写入，write()/send() 也会被阻塞，直到数据发送完毕缓冲区解锁，write()/send() 才会被唤醒。
//　　3) 如果要写入的数据大于缓冲区的最大长度，那么将分批写入。
//　　4) 直到所有数据被写入缓冲区 write()/send() 才能返回。
//　　当使用 read()/recv() 读取数据时：
//　　1) 首先会检查缓冲区，如果缓冲区中有数据，那么就读取，否则函数会被阻塞，直到网络上有数据到来。
//　 2) 如果要读取的数据长度小于缓冲区中的数据长度，那么就不能一次性将缓冲区中的所有数据读出，剩余数据将不断积压，直到有 read()/recv() 函数再次读取。
//　 3) 直到读取到数据后 read()/recv() 函数才会返回，否则就一直被阻塞。
//这就是TCP套接字的阻塞模式。所谓阻塞，就是上一步动作没有完成，下一步动作将暂停，直到上一步动作完成后才能继续，以保持同步性。
//如何接受大量数据
//因为缓冲区的存在，我们在传输大量数据时不能一下子全部传输完毕！事实上和接受和发送数据量，即send(1024)/recv(1024)关系不大。并不是我们将这两个值设置的很大和可以解决问题了。因为socket每次接收和发送都有最大数据量限制的，毕竟网络带宽也是有限的呀，不能一次发太多，发送的数据最大量的限制 就是缓冲区能缓存的数据的最大量，这个缓冲区的最大值在不同的系统上是不一样的，不过官方的建议是不超过8k,也就是8192。
//那么我们就只能从另一个角度来思考了，也就是说我要来判断一下，一个命令执行后，它返回的数据到底有没有完全传输完毕，如果没有，那么就继续传输，直到传完为止。
//在Linux中使用非阻塞的socket的情形下。
//（一）发送时
//当客户通过Socket提供的send函数发送大的数据包时，就可能返回一个EGGAIN的错误。
//该错误产生的原因是由于send 函数中的size变量大小超过了tcp_sendspace的值。
//tcp_sendspace定义了应用在调用send之前能够在kernel中缓存的数据量。
//当应用程序在socket中设置了O_NDELAY或者O_NONBLOCK属性后，如果发送缓存被占满，send就会返回EAGAIN的错误。

// 为了消除该错误，有三种方法可以选择： 
// 1.调大tcp_sendspace，使之大于send中的size参数 
// ---no -p -o tcp_sendspace=65536 
// 2.在调用send前，在setsockopt函数中为SNDBUF设置更大的值 
// 3.使用write替代send，因为write没有设置O_NDELAY或者O_NONBLOCK

//（二）接收时

//接收数据时常遇到Resource temporarily unavailable的提示，errno代码为11(EAGAIN)。
//这表明你在非阻塞模式下调用了阻塞操作，在该操作没有完成就返回这个错误，这个错误不会破坏socket的同步，
//不用管它，下次循环接着recv就可以。对非阻塞socket而言，EAGAIN不是一种错误。
//在VxWorks和 Windows上，EAGAIN的名字叫做EWOULDBLOCK。其实这算不上错误，只是一种异常而已。
//另外，如果出现EINTR即errno为4，错误描述Interrupted system call，操作也应该继续。
//最后，如果recv的返回值为0，那表明对方已将连接断开，我们的接收操作也应该结束。