#ifndef SQLFRIEND_H
#define SQLFRIEND_H

class QString;
class QSqlQuery;

class SQLFriend
{
public:
    SQLFriend();
    //添加好友列表
    static void insertFriend(QSqlQuery &query,QString &uid, QString &sub);

    //清空好友列表
    static void deleteFriend(QString &user);

    //清空好友详情
    static void deleteFriendInfo(QString &user);

    //读取好友列表
    static QSqlQuery selectFriends();
};

#endif // SQLFRIEND_H
