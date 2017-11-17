#include "SQLFriend.h"
#include "SQLManager.h"
#include "QSqlQuery.h"
#include <QDebug>

SQLFriend::SQLFriend()
{
}

//添加好友列表
void SQLFriend::insertFriend(QSqlQuery &query,QString &uid, QString &sub)
{
    //保存好友关系
    QString sql = "DELETE FROM XS_FriendList WHERE uid='"+uid+"'";
    bool b = query.exec(sql);
    if (!b) {
        qDebug() << "保存失败";
    }

    sql = "INSERT INTO XS_FriendList(uid,subscription) VALUES ('"+uid+"','"+sub+"')";
    b = query.exec(sql);
    if (!b) {
        qDebug() << "保存失败";
    }
}

//清空好友列表
void SQLFriend::deleteFriend(QString &user)
{
    QString sql = "";
    if (user != NULL) {
        sql = "DELETE from XS_FriendList WHERE uid = '"+user+"'";
    }else{
        sql = "DELETE from XS_FriendList";
    }
    bool b = SQLManager::getQuery().exec(sql);
    if (!b) {
        qDebug() << "保存失败";
    }
}
//清空好友详情
void SQLFriend::deleteFriendInfo(QString &user)
{
    QString sql = "";
    if (user != NULL) {
        sql = "DELETE from XS_UserProfile WHERE uid = '"+user+"'";
    }else{
        sql = "DELETE from XS_UserProfile";
    }
    bool b = SQLManager::getQuery().exec(sql);
    if (!b) {
        qDebug() << "保存失败";
    }
}
//读取好友列表
QSqlQuery SQLFriend::selectFriends()
{
    QString sql = "SELECT fl.subscription,up.uid,up.name,up.nick,up.avatar,up.signature FROM XS_FriendList AS fl ,XS_UserProfile AS up WHERE fl.uid = up.uid ";
    QSqlQuery query = SQLManager::getQuery();
    query.exec(sql);
    return query;
}
