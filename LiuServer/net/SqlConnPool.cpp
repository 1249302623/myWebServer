#include <mysql/mysql.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <list>
#include <pthread.h>
#include <iostream>
#include "SqlConnPool.h"
#include"Logging.h"
using namespace std;
SqlConnPool::SqlConnPool()
:mutex_(),cond_(mutex_)
{

}
//构造初始化
void SqlConnPool::start(string url, string User, string PassWord, string DBName, int Port, int MaxConn, int close_log)
{	
	m_CurConn = 0;
	m_FreeConn = 0;
	m_url = url;
	m_Port = Port;
	m_User = User;
	m_PassWord = PassWord;
	m_DatabaseName = DBName;
	m_close_log = close_log;

	for (int i = 0; i < MaxConn; i++)
	{
		MYSQL *con = NULL;
		con = mysql_init(con);

		if (con == NULL)
		{
			//LOG_ERROR<<"MySQL Error";
			exit(1);
		}
		con = mysql_real_connect(con, url.c_str(), User.c_str(), PassWord.c_str(), DBName.c_str(), Port, NULL, 0);

		if (con == NULL)
		{
			//LOG_ERROR<<"MySQL Error";
			exit(1);
		}
		connList.push_back(con);
		++m_FreeConn;
	}
	m_MaxConn = m_FreeConn;
}


//当有请求时，从数据库连接池中返回一个可用连接，更新使用和空闲连接数
MYSQL *SqlConnPool::GetConnection()
{
	MYSQL *con = NULL;
	MutexLockGuard lock(mutex_);
    while(connList.empty()){
        cond_.wait();
    }
    if(!connList.empty()){
		con = connList.front();
		connList.pop_front();
		--m_FreeConn;
		++m_CurConn;
	}
	return con;
}

//释放当前使用的连接
bool SqlConnPool::ReleaseConnection(MYSQL *con)
{
	if (NULL == con)
		return false;
	MutexLockGuard lock(mutex_);
	connList.push_back(con);
	++m_FreeConn;
	--m_CurConn;
	cond_.notify();
	con=NULL;
	return true;
}

//销毁数据库连接池
void SqlConnPool::DestroyPool()
{
	MutexLockGuard lock(mutex_);
	if (connList.size() > 0)
	{
		list<MYSQL *>::iterator it;
		for (it = connList.begin(); it != connList.end(); ++it)
		{
			MYSQL *con = *it;
			mysql_close(con);
		}
		m_CurConn = 0;
		m_FreeConn = 0;
		connList.clear();
	}
}

//当前空闲的连接数
int SqlConnPool::GetFreeConn()
{
	return this->m_FreeConn;
}

SqlConnPool::~SqlConnPool()
{
	DestroyPool();
}

SqlConnRAII::SqlConnRAII(SqlConnPool *connPool){
	conRAII = connPool->GetConnection();
	poolRAII = connPool;
}

SqlConnRAII::~SqlConnRAII(){
	poolRAII->ReleaseConnection(conRAII);
	//printf("析构\n");
}

bool SqlConnRAII::ExeSQL(string sql)
{
    /*执行失败*/
    if(mysql_query(conRAII,sql.c_str()))
    {
        cout << "query fail: " << mysql_error(conRAII);
        exit(1);                                                                                                      
    }
    else
    {
        /*获取结果集*/
        result = mysql_store_result(conRAII);
        int fieldnum = mysql_num_fields(result);
        for(int i=0; i<fieldnum; i++)
        {
            row = mysql_fetch_row(result);
            if(row <= 0)
            break;
            for(int j=0; j<fieldnum; j++)
            {
            cout << row[j] << "\t\t"<< endl;;
            }
            
        }
        mysql_free_result(result);
    }
    return true;
} 