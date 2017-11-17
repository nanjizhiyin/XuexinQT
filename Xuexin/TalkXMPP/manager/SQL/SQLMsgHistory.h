#ifndef SQLMSGHISTORY_H
#define SQLMSGHISTORY_H

#include <QObject>
#include "EnumManager.h"

class QSqlQuery;
class QXmppMessage;

class SQLMsgHistory : public QObject
{
    Q_OBJECT
public:
    explicit SQLMsgHistory(QObject *parent = 0);

    //保存聊天记录
    static void insertMessage(const QXmppMessage &message);

    //保存body聊天记录
    static void insertBodyMessageByBody(QString &body,
                                        QString &messageID,
                                        QString &chatID,
                                        QString &fromUser,
                                          XXEnum::XXMessageSendStatus status,
                                      long long createDate,
                                        XXEnum::XXChatType chatType,
                                           bool isAdd);


    //读取好友列表
    static QSqlQuery selectMessage(QString &user, long long createDate);

signals:

public slots:

};

#endif // SQLMSGHISTORY_H
