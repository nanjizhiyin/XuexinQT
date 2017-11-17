#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

class QString;
class QSqlQuery;
class QSqlDatabase;

class SQLManager
{
public:
    SQLManager();

    //初始化
    static void init();
    //打开此用户专用db
    static void openDB(QString &user);
    //
    static QSqlDatabase getUserDB();
    //
    static QSqlQuery getQuery();
};

#endif // SQLITEMANAGER_H
