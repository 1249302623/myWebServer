#include"Timestamp.h"
#include<vector>
#include"Test.h"
void passByConstReference(const Timestamp& x)
{
  printf("%s\n", x.toString().c_str());
}

void passByValue(Timestamp x)
{
  printf("%s\n", x.toString().c_str());
}

void benchmark()
{
  const int kNumber = 1000*10;

  // 创建一个KNumber大小的stamps
  std::vector<Timestamp> stamps;
  
  //将kNumber大小个个Timestamp放置到该向量中，时间为当前时间
  for (int i = 0; i < kNumber; ++i)
  {
    Timestamp now(Timestamp::now());
    stamps.push_back(now);
  }
  //打印第一个和最后一个Timestamp对象
  printf("%s\n", stamps.front().toString().c_str());
  printf("%s\n", stamps.back().toString().c_str());
  //计算第一个和最后一个对象时间差
  printf("%f\n", timeDifference(stamps.back(), stamps.front()));
  printf("%s\n",stamps.front().toFormattedString(true).c_str());
  printf("%s\n",stamps.back().toFormattedString(true).c_str());
}

int Timestamp_test_main()
{
  Timestamp now(Timestamp::now());//构造函数初始化一个Timestamp，时间为当前时间
  printf("%s\n", now.toString().c_str());//打印当前时间微秒数
  passByValue(now);//打印当前时间微秒数
  passByConstReference(now);//打印当前时间微秒数
  benchmark();
  return 0;
}