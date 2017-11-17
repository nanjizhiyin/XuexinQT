#ifndef SQLMEMBER_H
#define SQLMEMBER_H

class QString;
class QSqlQuery;
class SQLMember
{
public:
    SQLMember();

    //初始化
    static void init();

    //登录登记资料
    static QSqlQuery selectUsers();

    //登录者账号密码
    static void saveUserAndPassword(const QString& username, const QString& password);

    //删除所有账号和密码
    static void deleteAllUserAndPassword();
};

#endif // SQLMEMBER_H
