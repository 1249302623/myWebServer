#include"Test.h"
#include"SqlConnPool.h"
#include"Singleton.h"
void sqlPoolTest(){
    Singleton<SqlConnPool>::instance().start(
        "localhost",
        "root",
        "124930",
        "LiuServer",
        0,5, 0);
    {
    SqlConnRAII sqlconn(&Singleton<SqlConnPool>::instance());
    sqlconn.ExeSQL("SELECT * FROM students;");
    }
}