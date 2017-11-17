#include "SQLMsgHistory.h"
#include "SQLManager.h"
#include "qsqlquery.h"
#include "qvariant.h"
#include "qdebug.h"
#include "QXmppMessage.h"
#include "QXmppUtils.h"
#include <QDomElement>


SQLMsgHistory::SQLMsgHistory(QObject *parent) :
    QObject(parent)
{
}

//保存聊天记录
void SQLMsgHistory::insertMessage(const QXmppMessage &message)
{
    QString recentlyTitle = "";//学信页显示的文字
    QString content = "";
    QString src = "";
    QString localPath = "";
    int      imageWidth = 0;
    int      imageHeight = 0;
    int      audioPlayTime = 0;//录音的长度
    QXmppMessage::MessageType messageType = message.messageType();
    if (messageType == QXmppMessage::Body) {//文字
        content = message.body();
    }
    else if (messageType == QXmppMessage::Audio) {//录音
        recentlyTitle = content = "[语音]";
    }
    else if (messageType == QXmppMessage::Image) {//图片
        recentlyTitle = content = "[图片]";
    }
    else if (messageType == QXmppMessage::Video) {
        recentlyTitle = content = "[视频]";
    }
    else if (messageType == QXmppMessage::Text) {
        recentlyTitle = content = message.text();
    }
    else if (messageType == QXmppMessage::AM) {
        content = message.am();
    }
    else if (messageType == QXmppMessage::ST) {
        content = message.st();
    }
    else if (messageType == QXmppMessage::MT) {
        content = message.mt();
    }
    else if (messageType == QXmppMessage::Pay) {
        content = message.pay();
    }
    else{
        return;
    }

    QDateTime datetime = message.stamp();
    long long msgTimeInt = datetime.toTime_t()*1000.0;
    qDebug() << "msgTimeInt = " << datetime << msgTimeInt;

    //-----------------------
    //保存到学信页
//    NSString *chatingUser = [ViewManager rootViewController].chatingUser;

//    BOOL tmpIsAdd = TRUE;
//    //正在和此人聊天
//    if ([chatID isEqual:chatingUser]) {
//        tmpIsAdd = FALSE;
//    }

    QString chatID = QXmppUtils::jidToUser(message.from());
    QString fromUID = chatID;

    QString messageID = message.id();
    QXmppMessage::Type chatType = message.type();

    QString insertSql = "INSERT INTO XS_MsgHistory"
            "(chatID,fromUID,msgID,msgType,content,src,localPath,createDate,sendStatus,width,height,playTime,chatType) "
            "VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)";


    QSqlQuery query = SQLManager::getQuery();
    query.prepare(insertSql);

    query.addBindValue(chatID);
    query.addBindValue(fromUID);
    query.addBindValue(messageID);
    query.addBindValue(messageType);
    query.addBindValue(content);
    query.addBindValue(src);
    query.addBindValue(localPath);
    query.addBindValue(msgTimeInt);
    query.addBindValue(XXEnum::XXMessageSendSuccess);
    query.addBindValue(imageWidth);
    query.addBindValue(imageHeight);
    query.addBindValue(audioPlayTime);
    query.addBindValue(chatType);

    bool bSuccess = query.exec();
    if (!bSuccess)
    {
        qDebug() << "保存失败11" << insertSql;
    }
}
//保存body聊天记录
void SQLMsgHistory::insertBodyMessageByBody(QString &body,
                                            QString &messageID,
                                            QString &chatID,
                                            QString &fromUser,
                                              XXEnum::XXMessageSendStatus status,
                                          long long createDate,
                                            XXEnum::XXChatType chatType,
                                               bool isAdd)
{

    QString sqlStr = "insert into XS_MsgHistory(chatID, fromUID,msgID,content,msgType,createDate,sendStatus,chatType)"
                     "values(?, ?, ?, ?, ?, ?,?, ?)";
    QSqlQuery query = SQLManager::getQuery();
    query.prepare(sqlStr);

    query.addBindValue(chatID);
    query.addBindValue(fromUser);
    query.addBindValue(messageID);
    query.addBindValue(body);
    query.addBindValue(QXmppMessage::Body);
    query.addBindValue(createDate);
    query.addBindValue(status);
    query.addBindValue(chatType);

    bool bSuccess = query.exec();
    if (!bSuccess)
    {
        qDebug() << "保存失败" << sqlStr;
    }

}
//读取好友列表
QSqlQuery SQLMsgHistory::selectMessage(QString &user, long long createDate)
{
    QString sqlStr = "SELECT * FROM XS_MsgHistory WHERE chatID = ? AND createDate < ?  ORDER BY createDate desc,ID desc LIMIT 10 ";
    qDebug() << "sql" << user << createDate;
    QSqlQuery query = SQLManager::getQuery();
    query.prepare(sqlStr);

    query.addBindValue(user);
    query.addBindValue(createDate);

    bool bSuccess = query.exec();
    if (!bSuccess)
    {
        qDebug() << "失败" << sqlStr;
    }

    return query;
}
