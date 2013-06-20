#include <map>
#include <stdio.h>
#include <string> 
#include <time.h> 
#include <vector>
#include <assert.h>
#include <string.h> 
using namespace std; 

const char  T_USER []= "user"; 
const char  T_SERVER [] = "server"; 
const char  T_TIMESTAMP [] = "timestamp"; 
const char  T_EVENT []		= "event" ;
const char  T_EVT_LOGIN [] = "login"; 
const char  T_EVT_LOGOUT[]  = "logout";

const char  T_URL [] = "url";
const char  T_ACTION []= "action"; 
const char  T_ACTION_POST [] = "post"; 
const char  T_ACTION_GET [] = "get"; 
const char  T_FLOW [] = "flow"; 

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

struct UserFlowStat
{
	int handle_userflow(char * line);

	int handle_userflow(map<string, string> & fieldsMap);

	int handle_userlog(map<string, string> & fieldsMap);

	UserInfoMAP userFlows_;
};

void splitLine(char * line, const char* delim, std::vector<string> & fields) 
{
	char * pCur = strtok(line, delim);

	while (pCur != NULL)
	{
		while (*pCur == ' ') 
		{
			pCur++;
		}
		
		fields.push_back(pCur);
		pCur = strtok(0, delim);
	}
}

int UserFlowStat::handle_userflow(char *line ) 
{
	assert(line);
	vector<string> fields; 

	splitLine(line, ",=", fields); 

	if (fields.size() == 0 || fields.size() %2 != 0) 
	{
		printf(" invalid line %s \n", line) ;
		return -1;
	}

	map<string, string> fieldsMap; 

	for (int i = 0; i < fields.size(); i+=2) 
	{
		const std::string & key =  fields[i];
		const std::string  & value = fields[i+1]; 
		fieldsMap.insert(make_pair(key, value));
	}
		
	if (fieldsMap.find(T_URL) != fieldsMap.end()) 
	{
		return handle_userflow(fieldsMap);
	}
	else
	{
		return handle_userlog(fieldsMap);
	}
	return 0;
}


int UserFlowStat::handle_userflow(map<string, string> & fieldsMap)
{

	return 0;
}

int UserFlowStat::handle_userlog(map<string, string> & fieldsMap)
{

	return 0;
}

void staticNetworkStat(FILE * in, FILE * out) 
{
	if (in == NULL || out == NULL ) 
		return; 


	UserFlowStat flowStat;


	char line[256];
	while ( fgets(line, sizeof(line), in) != NULL) 
	{
		char * ptr = 0; 
		if( (ptr= strchr(line, '\n')) != NULL) 
		{
			*ptr = 0;
		}	

		flowStat.handle_userflow(line);
	}
}

int main( int argc ,char ** argv )
{

	char inFileName[] = "userflow.txt"; 
	char outFileName[] = "out.txt";
	
	FILE * inFile = fopen(inFileName, "r");
	if (inFile == NULL )
	{
		printf("open %s failed\n", inFileName);
		return -1;
	}

	FILE * outFile = fopen (outFileName, "w+"); 
	if (outFile == NULL) 
	{
		printf ("open %s failed \n", outFileName);

		return -1;
	}

	staticNetworkStat(inFile, outFile);

}
