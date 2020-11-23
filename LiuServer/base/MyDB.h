#pragma once
#include <string>
#include <iostream>
#include <mysql/mysql.h>
using namespace std;
 
class MyDB
{ 
public:
    MyDB();
    ~MyDB();                                                 
    bool ExeSQL(string sql);
private:
    MYSQL* mysql;
    MYSQL_ROW row;
    MYSQL_RES* result;
    MYSQL_FIELD* field;                                                                                               
};
                                                                                                                     