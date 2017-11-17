#include "SQLMember.h"
#include <QtSql>

static QSqlDatabase memberDB;

SQLMember::SQLMember()
{
}
void SQLMember::init()
{
    memberDB = QSqlDatabase::addDatabase("QSQLITE","system");    //添加数据库驱动
    memberDB.setDatabaseName("system.db");  //在工程目录新建一个mytest.db的文件
    if(!memberDB.open())    {
           qDebug()<<"public创建失败";
           return;
    }

    QSqlQuery query(memberDB);//以下执行相关QSL语句

    //新建XS_LoginList表
    QString sql = "CREATE TABLE IF NOT EXISTS XS_LoginList \
            (ID INTEGER PRIMARY KEY AUTOINCREMENT,username TEXT,password TEXT)";
    bool b = query.exec(sql);
    if(!b)
        qDebug()<<"XS_LoginList创建:" << b;
}
//读取账号和密码
QSqlQuery SQLMember::selectUsers()
{
    QSqlQuery query(memberDB);
    query.exec("SELECT * FROM XS_LoginList");
    return query;
}

//登录者账号密码
void SQLMember::saveUserAndPassword(const QString& username, const QString& password)
{
    QSqlQuery query(memberDB);
    query.prepare("INSERT INTO XS_LoginList (username,password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    bool b = query.exec();
    if(!b)
        qDebug()<<"saveUserAndPassword:" << b;
}
//删除所有账号和密码
void SQLMember::deleteAllUserAndPassword()
{
    QSqlQuery query(memberDB);
    bool b = query.exec("DELETE FROM XS_LoginList");
    if(!b)
        qDebug()<<"deleteAllUserAndPassword:" << b;
}
