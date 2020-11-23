#include"Timestamp.h"
#include<stdint.h>
#include<inttypes.h>
#include<sys/time.h>
//以秒的形式输出Timestamp中时间，精确到微秒
std::string Timestamp::toString() const
{
  char buf[32] = {0};
  int64_t seconds = microSecondsSinceEpoch_ /kMicroSecondsPerSecond;
  int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
  snprintf(buf, sizeof(buf)-1, "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
  return buf;
}

//将当前Timestamp时间对象格式化输出为年月日时分秒格式，如果选择了showMicroseconds，那么将精确到微秒
std::string Timestamp::toFormattedString(bool showMicroseconds) const
{
  char buf[64] = {0};
  time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
  struct tm tm_time;
  gmtime_r(&seconds, &tm_time);

  if (showMicroseconds)
  {
    int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
    snprintf(buf, sizeof(buf), "%4d-%02d-%02d %02d:%02d:%02d.%06d",
             tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
             tm_time.tm_hour+8, tm_time.tm_min, tm_time.tm_sec,
             microseconds);//+8,中国时区
  }
  else
  {
    snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
             tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
             tm_time.tm_hour+8, tm_time.tm_min, tm_time.tm_sec);
  }
  return buf;
}

// 获取当前时间，将当前时间转化为微秒并返回一个Timestamp对象
Timestamp Timestamp::now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  int64_t seconds = tv.tv_sec;
  Timestamp t(seconds * kMicroSecondsPerSecond + tv.tv_usec);
  return t;
}
