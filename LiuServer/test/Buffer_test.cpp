#include"Buffer.h"
#include"Test.h"
#include<string>
void Buffer_test_main(){
  Buffer buf;
  bool s=buf.readableBytes()==0;
  s=buf.writableBytes()==Buffer::kInitialSize;
  s=buf.prependableBytes()== Buffer::kCheapPrepend;
  
  std::string str="";
  for(int i=0;i<200;i++)
    str+='e';
  buf.append(str);
  s=buf.readableBytes()==str.size();
  s=buf.writableBytes()==Buffer::kInitialSize - str.size();
  s=buf.prependableBytes()==Buffer::kCheapPrepend;

  const std::string str2 =  buf.retrieveAsString(50);
  s=str2.size()==50;
  s=buf.readableBytes()==str.size() - str2.size();
  s=buf.writableBytes()==Buffer::kInitialSize - str.size();
  s=buf.prependableBytes()==Buffer::kCheapPrepend + str2.size();

  buf.append(str);
  s=buf.readableBytes()== 2*str.size() - str2.size();
  s=buf.writableBytes()== Buffer::kInitialSize - 2*str.size();
  s=buf.prependableBytes()== Buffer::kCheapPrepend + str2.size();

  const std::string str3 =  buf.retrieveAllAsString();
  s=str3.size()==350;
  s=buf.readableBytes()== 0;
  s=buf.writableBytes()==Buffer::kInitialSize;
  s=buf.prependableBytes()==Buffer::kCheapPrepend;
}