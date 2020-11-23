#pragma once

#include <stdio.h>
#include <list>
#include <mysql/mysql.h>
#include <error.h>
#include <string.h>
#include <iostream>
#include <string>
#include"MutexLock.h"
#include"CountDownLatch.h"

using namespace std;

class SqlConnPool
{
public:
	MYSQL *GetConnection();				 //获取数据库连接
	bool ReleaseConnection(MYSQL *conn); //释放连接
	int GetFreeConn();					 //获取连接
	void DestroyPool();					 //销毁所有连接

	SqlConnPool();
	void start(string url, string User, string PassWord, string DBName, int Port, int MaxConn, int close_log);

	~SqlConnPool();
private:
	int m_MaxConn;  //最大连接数
	int m_CurConn;  //当前已使用的连接数
	int m_FreeConn; //当前空闲的连接数
	MutexLock mutex_;
	list<MYSQL *> connList; //连接池
	Condition cond_;
public:
	string m_url;			 //主机地址
	string m_Port;		 //数据库端口号
	string m_User;		 //登陆数据库用户名
	string m_PassWord;	 //登陆数据库密码
	string m_DatabaseName; //使用数据库名
	int m_close_log;	//日志开关
};

class SqlConnRAII{
public:
	SqlConnRAII(SqlConnPool *connPool);
	~SqlConnRAII();
	bool ExeSQL(string sql);
	bool sqlQuery(string sql){
		if(mysql_query(conRAII,sql.c_str()))//失败
			return false;
		else{
			result = mysql_store_result(conRAII);
        	int num = mysql_num_rows(result);
			mysql_free_result(result);
			if(num>=1)
				return true;
		}
		return false;
	}
	bool sqlinsert(string sql){
		if(mysql_query(conRAII,sql.c_str()))//失败
			return false;
		else{
			//result = mysql_store_result(conRAII);
			//mysql_free_result(result);
			return true;
		}
	}

private:
	MYSQL *conRAII;
	SqlConnPool *poolRAII;
	MYSQL_ROW row;
    MYSQL_RES* result;
    MYSQL_FIELD* field;  
};

