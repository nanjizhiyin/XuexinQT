#include "SQLManager.h"
#include <QtSql>
#include "SQLMember.h"

static QSqlDatabase kUserDB;


SQLManager::SQLManager()
{
}


void SQLManager::init()
{
    SQLMember::init();
}
QSqlDatabase SQLManager::getUserDB()
{
    return kUserDB;
}
QSqlQuery SQLManager::getQuery()
{
    return QSqlQuery(kUserDB);
}
void SQLManager::openDB(QString &user)
{

    kUserDB = QSqlDatabase::addDatabase("QSQLITE",user);    //添加数据库驱动
    kUserDB.setDatabaseName(user + ".db");  //在工程目录新建一个mytest.db的文件
    if(!kUserDB.open())    {
           qDebug()<<"public创建失败";
           return;
    }
    QSqlQuery query(kUserDB);


    //好友列表
    QString friendListSql = "CREATE TABLE IF NOT EXISTS XS_FriendList "
            "(ID INTEGER PRIMARY KEY AUTOINCREMENT,uid TEXT NOT NULL UNIQUE,subscription TEXT)";
    bool b = query.exec(friendListSql);
    if(!b){
        qDebug()<<"XS_FriendList创建失败";
    }

    //好友信息
    QString userProfileSql = "CREATE TABLE IF NOT EXISTS XS_UserProfile "
            "(ID INTEGER PRIMARY KEY AUTOINCREMENT,uid TEXT NOT NULL UNIQUE,name TEXT,namepp TEXT,"
            "avatar TEXT,gender INTEGER DEFAULT 0,signature TEXT,nick TEXT,nickpp TEXT,"
            "mobile TEXT,country TEXT,province TEXT,city TEXT,district TEXT,modificationDate TEXT,birthday TEXT,sno TEXT)";
    b = query.exec(userProfileSql);
    if(!b){
        qDebug()<<"XS_UserProfile创建失败";
    }

    //新朋友
    QString newFriendsSql = "CREATE TABLE IF NOT EXISTS XS_NewFriends "
            "(ID INTEGER PRIMARY KEY AUTOINCREMENT,uid TEXT NOT NULL UNIQUE,type TEXT,status TEXT,isViewed BOOLEAN DEFAULT 0)";
    b = query.exec(newFriendsSql);
    if(!b){
        qDebug()<<"XS_NewFriends创建失败";
    }

    //聊天记录
    QString msgHistorySql = "CREATE TABLE IF NOT EXISTS XS_MsgHistory (ID INTEGER PRIMARY KEY AUTOINCREMENT,msgID  TEXT NOT NULL UNIQUE,"
            "chatID TEXT  NOT NULL,fromUID TEXT  NOT NULL,msgType INTEGER,content TEXT,src TEXT,localPath TEXT,"
            "createDate INT8,sendStatus INTEGER DEFAULT 1,width INTEGER,height INTEGER,playTime INTEGER,played BOOLEAN DEFAULT 0,chatType INTEGER DEFAULT 0)";
    b = query.exec(msgHistorySql);
    if(!b){
        qDebug()<<"XS_MsgHistory";
    }
}
