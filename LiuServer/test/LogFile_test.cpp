#include<memory>
#include"Test.h"
#include"LogFile.h"
#include<stdio.h>
#include<string.h>
#include"Logging.h"
#include <unistd.h>
#include"Timestamp.h"
int LogFile_test_main()
{

  std::string line = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
  Timestamp start = Timestamp::now();
  for (int i = 0; i < 10; ++i)
  {
      for(int j=0;j<100;j++){
      LOG_INFO<<"--"<<line<<i;
      //usleep(10);
      }
  }
  Timestamp end = Timestamp::now();
  printf("%f\n", timeDifference(end, start)*1000000);
  printf("完结\n");
  sleep(5);
}