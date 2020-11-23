#pragma once
#include <algorithm>
#include <vector>
#include <assert.h>
#include <string.h>
#include<string>
#include"Util.h"
#include"MutexLock.h"
/// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
///
/// @code
/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// @endcode
class Buffer
{
public:
  static const size_t kCheapPrepend = 8;//prependable区的长度
  static const size_t kInitialSize = 1024;

  Buffer()
    : buffer_(kCheapPrepend + kInitialSize),
      readerIndex_(kCheapPrepend),
      writerIndex_(kCheapPrepend)
  {
    assert(readableBytes() == 0);
    assert(writableBytes() == kInitialSize);
    assert(prependableBytes() == kCheapPrepend);
  }

  // default copy-ctor, dtor and assignment are fine

  void swap(Buffer& rhs)
  {
    buffer_.swap(rhs.buffer_);
    std::swap(readerIndex_, rhs.readerIndex_);
    std::swap(writerIndex_, rhs.writerIndex_);
  }
// writerIndex_ - readerIndex_代表还能从buffer中读出多少字节
  size_t readableBytes() const
  { return writerIndex_ - readerIndex_; }
// size - writerIndex_代表buffer还能写入多少字节
  size_t writableBytes() const
  { return buffer_.size() - writerIndex_; }
// 此时的预留空间为多少 此时readIndex前面的空间都可以作为预留空间
  size_t prependableBytes() const
  { return readerIndex_; }
// 获取可读数据的指针地址，类似vector的data
  const char* peek() const
  { return begin() + readerIndex_; }

  // retrieve returns void, to prevent
  // string str(retrieve(readableBytes()), readableBytes());
  // the evaluation of two functions are unspecified
  // 提取len字节的数据
  void retrieve(size_t len)
  {
    assert(len <= readableBytes());
    if (len < readableBytes())
    {
      readerIndex_ += len;
    }
    else
    {
      // 当全部提取时，不仅readerIndex要移动，writeIndex也必须移动
      retrieveAll();
    }
  }
  // 提取end之前的所有字节
  void retrieveUntil(const char* end)
  {
    assert(peek() <= end);
    assert(end <= beginWrite());
    retrieve(end - peek());
  }
   // 提取一个64位整数
  void retrieveInt64()
  {
    retrieve(sizeof(int64_t));
  }
    // 提取一个32位整数
  void retrieveInt32()
  {
    retrieve(sizeof(int32_t));
  }
  // 提取一个16位整数
  void retrieveInt16()
  {
    retrieve(sizeof(int16_t));
  }
  // 提取一个8字节整数
  void retrieveInt8()
  {
    retrieve(sizeof(int8_t));
  }
  // 提取所有字节，注意writeIndex也必须更改
  void retrieveAll()
  {
    readerIndex_ = kCheapPrepend;
    writerIndex_ = kCheapPrepend;
  }
  // 提取所有的字节，作为一个string返回
  std::string retrieveAllAsString()
  {
    return retrieveAsString(readableBytes());;
  }
  // 提取len字节，作为string返回
  std::string retrieveAsString(size_t len)
  {
    assert(len <= readableBytes());
    std::string result(peek(), len);
    retrieve(len);
    return result;
  }

  std::string toString() const
  {
    return std::string(peek(), static_cast<int>(readableBytes()));
  }
 // 将String的字节扩充在buffer尾部
  void append(const std::string& str)
  {
    append(str.c_str(), str.size());
  }
  // 写入长度为len的字节
  void append(const char* data, size_t len)
  {
    ensureWritableBytes(len);
    std::copy(data, data+len, beginWrite());
    hasWritten(len);
  }
  // 写入长度为len的void*类型
  void append(const void* data, size_t len)
  {
    append(static_cast<const char*>(data), len);
  }

  // 确保缓冲区可写空间>=len，如果不足则扩充
  void ensureWritableBytes(size_t len)
  {
    if (writableBytes() < len)
    {
      makeSpace(len);
    }
    assert(writableBytes() >= len);
  }
  // 返回开始写入的位置
  char* beginWrite()
  { return begin() + writerIndex_; }

  const char* beginWrite() const
  { return begin() + writerIndex_; }
 // 写入len字节的后续处理
  void hasWritten(size_t len)
  { writerIndex_ += len; }

  void appendInt8(int8_t x)
  {
    append(&x, sizeof x);
  }

  int8_t readInt8()
  {
    int8_t result = peekInt8();
    retrieveInt8();
    return result;
  }

  int8_t peekInt8() const
  {
    assert(readableBytes() >= sizeof(int8_t));
    int8_t x = *peek();
    return x;
  }


  void prependInt8(int8_t x)
  {
    prepend(&x, sizeof x);
  }
    // 预留位置，填充len字节数据
  void prepend(const void*  data, size_t len)
  {
    assert(len <= prependableBytes());
    readerIndex_ -= len;
    const char* d = static_cast<const char*>(data);
    std::copy(d, d+len, begin()+readerIndex_);
  }
  // 缩减内存，至reserve大小
  // 收缩，保留reserve个字节
  void shrink(size_t reserve)
  {
    // FIXME: use vector::shrink_to_fit() in C++ 11 if possible.
    Buffer other;
    other.ensureWritableBytes(readableBytes()+reserve);
    other.append(toString());
    swap(other);
  }

  /// Read data directly into buffer.
  ///
  /// It may implement with readv(2)
  ssize_t readFd(int fd);
  ssize_t readFdET(int fd);
  // ssize_t readFdinMutex(int fd){
  //   MutexLockGuard lock(mutex_);
  // }
private:

  char* begin()
  { return &*buffer_.begin(); }

  const char* begin() const
  { return &*buffer_.begin(); }

  void makeSpace(size_t len)
  {
    if (writableBytes() + prependableBytes() < len + kCheapPrepend)
    {
      // FIXME: move readable data
      buffer_.resize(writerIndex_+len);
    }
    else
    {
      // move readable data to the front, make space inside buffer
      assert(kCheapPrepend < readerIndex_);
      size_t readable = readableBytes();
      std::copy(begin()+readerIndex_,
                begin()+writerIndex_,
                begin()+kCheapPrepend);
      readerIndex_ = kCheapPrepend;
      writerIndex_ = readerIndex_ + readable;
      assert(readable == readableBytes());
    }
  }

 private:
  std::vector<char> buffer_;	// vector用于替代固定大小数组
  size_t readerIndex_;			// 读位置
  size_t writerIndex_;			// 写位置
  MutexLock mutex_;
};