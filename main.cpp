// OJ.cpp : Defines the entry point for the console application.

#include <map>
#include <stdio.h>
#include <string> 
#include <time.h> 


using namespace std; 

struct FlowInfo 
{
  string host; 
  int getCnt; 
  int postCnt;
};

typedef map<string, FlowInfo> FlowInfoMAP; 

struct UserInfo 
{
    int userId;
    bool isLogin; 
    int loginTime;
    FlowInfoMAP  flowMap;
}; 


typedef map<int, UserInfo>  UserInfoMAP; 

UserInfoMAP userMap_;

#define MAX_USER_COUNT   1000000
int main() 
{
   time_t start = time(0);
   UserInfo info ; 
   info.isLogin = false;

   for (int i =0; i< MAX_USER_COUNT; i ++)
   {
       userMap_.insert(make_pair(i,  info));
   } 
   
   for (int i =0; i< MAX_USER_COUNT; i ++)
   {
     UserInfo & info = userMap_[i];
     info.isLogin = false;
   } 

   for (int i =0; i< MAX_USER_COUNT; i ++)
   {
     UserInfo & info = userMap_[i];
     info.isLogin = false;
   } 
   
   for (int i =0; i < MAX_USER_COUNT; i++)
   {
     UserInfo & info = userMap_[i];
     FlowInfo flowInfo ;
     flowInfo.host = "www.taobao.com"; 
     flowInfo.getCnt = 1; 
     info.flowMap.insert(make_pair(flowInfo.host, flowInfo));
   }  

   for (int i =0; i < MAX_USER_COUNT; i++)
   {
     UserInfo & info = userMap_[i];
     FlowInfo flowInfo ;
     flowInfo.host = "www.baidu.com"; 
     flowInfo.getCnt = 1; 
     info.flowMap.insert(make_pair(flowInfo.host, flowInfo));
   }  

   time_t end = time(0) ;
   printf("insert time %d", (end -start));
}

