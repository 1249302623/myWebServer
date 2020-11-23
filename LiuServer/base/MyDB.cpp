#include <iostream>
#include <string>
#include <stack>
#include <algorithm>      
#include <mysql/mysql.h>  
#include "MyDB.h"

using namespace std;

MyDB::MyDB()    
{         
}

MyDB::~MyDB()
{                                                                                                                     
}


bool MyDB::ExeSQL(string sql)
{
    /*执行失败*/
    if(mysql_query(mysql,sql.c_str()))
    {
        cout << "query fail: " << mysql_error(mysql);
        exit(1);                                                                                                      
    }
    else
    {
        /*获取结果集*/
        result = mysql_store_result(mysql);
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