#include <errno.h>
#include <sys/uio.h>
#include"Buffer.h"
#include"Util.h"
#include"Logging.h"
//由于作者水平有限，只是摘抄了别人的ET方式读写数据的方法，未能在Buffer中实现ET操作
//有兴趣的可以写一个对buffer进行ET操作的方法。
// 结合栈上的空间，避免内存使用过大，提高内存使用率
// 如果每个链接分配固定缓冲区，假设64k,有5K个连接，每个连接就分配64K+64K的缓冲区的话，将占用640M内存，
// 而大多数时候，这些缓冲区的使用率很低
ssize_t Buffer::readFd(int fd)
{
  // saved an ioctl()/FIONREAD call to tell how much to read
  // 节省一次ioctl系统调用（获取有多少可读数据）
  char extrabuf[65536];
  struct iovec vec[2];
  const size_t writable = writableBytes();
  // 第一块缓冲区
  vec[0].iov_base = begin()+writerIndex_;
  vec[0].iov_len = writable;
  // 第二块缓冲区
  vec[1].iov_base = extrabuf;
  vec[1].iov_len = sizeof extrabuf;
  const ssize_t n = readvLT(fd, vec, 2);
  if (n < 0)
  {
    //LOG_ERROR<<"read Buffer error";
  }
  else if (static_cast<size_t>(n) <= writable)	//第一块缓冲区足够容纳
  {
    writerIndex_ += n;
  }
  else		// 当前缓冲区，不够容纳，因而数据被接收到了第二块缓冲区extrabuf，将其append至buffer
  {
    writerIndex_ = buffer_.size();
    append(extrabuf, n - writable);
  }
  return n;
}