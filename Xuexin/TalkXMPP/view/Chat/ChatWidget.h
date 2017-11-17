#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include "EnumManager.h"

class QXmppMessage;
class QScrollArea;
class QFrame;
class QVBoxLayout;
class QTextEdit;
class QPushButton;
class QListWidget;

class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWidget(QWidget *parent = 0);
    ~ChatWidget();

    QString user;
    XXEnum::XXChatType chatType;
    void setUser(const QString &jid);
private:

    long long lastDate;//最后一条消息的时间

    QListWidget     *listWidget;

    QVBoxLayout  *rootLayout;
    QTextEdit    *sendText;
    QPushButton  *previousBt;//上一页消息
    QPushButton  *sendButton;//发送按钮
private:
    //插入聊天
    void insertHtml(const QString &message,int orientation = 0);


signals:

public slots:
    void messageReceived(const QXmppMessage &message);
    void presenceChanged(const QString& bareJid,const QString& resource);

private slots:
    void _q_send();
    //显示聊天记录
    void selectHistoryMsg();
};

#endif // CHATWIDGET_H
