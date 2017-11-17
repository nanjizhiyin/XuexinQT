#include "ChatWidget.h"
#include "Utils.h"
#include <QScrollArea>
#include <QFrame>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QTextBrowser>
#include <QScrollBar>
#include <SignalManager.h>
#include <ViewManager.h>
#include <qlabel.h>
#include <QSqlQuery>
#include "SQLMsgHistory.h"
#include <QListWidget>
#include "chatcell.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(QSize(400,400));
    this->setAttribute(Qt::WA_DeleteOnClose,true);


    lastDate = QDateTime::currentDateTime().toTime_t()*1000.0;


    sendText = new QTextEdit(this);
    sendText->setFixedHeight(80);

    previousBt = new QPushButton(this);
    previousBt->setFixedHeight(40);
    previousBt->setText(tr("上一页"));
    connect(previousBt, SIGNAL(released()), this, SLOT(selectHistoryMsg()));

    sendButton = new QPushButton(this);
    sendButton->setFixedHeight(40);
    sendButton->setText(tr("发送"));
    connect(sendButton, SIGNAL(released()), this, SLOT(_q_send()));

    listWidget = new QListWidget();

    rootLayout = new QVBoxLayout(this);
    rootLayout->setMargin(1);
    rootLayout->addWidget(previousBt);
    rootLayout->addWidget(listWidget,1);
    //rootLayout->addSpacing(5);//添加20水平宽度的空白 b类型 垂直方向
    //rootLayout->addStretch(10);// 添加一个固定长度的延伸
    rootLayout->addWidget(sendText);
    rootLayout->addWidget(sendButton);

    //收到新消息
    SignalManager *obj = &SignalManager::sharedManager();
    connect(obj,SIGNAL(signal_recvMessage(QXmppMessage)),SLOT(messageReceived(QXmppMessage)));
}
//////
void ChatWidget::presenceChanged(const QString& bareJid,const QString& resource)
{
    qDebug("example_2_rosterHandling:: Presence changed %s/%s", qPrintable(bareJid), qPrintable(resource));
}
void ChatWidget::messageReceived(const QXmppMessage &message)
{
    qDebug()<<"messageReceived="<<message.body();
    QString body = message.body();
    if(!body.isEmpty()){
        //显示内容
        insertHtml(message.body());
    }
}
void ChatWidget::setUser(const QString &jid)
{
    qDebug()<<"shopchat="<<jid;
    user = jid;
    this->selectHistoryMsg();

}


//显示聊天记录
void ChatWidget::selectHistoryMsg()
{
    //读取消息
    QSqlQuery query = SQLMsgHistory::selectMessage(this->user,this->lastDate);
    while (query.next()) {
        lastDate = query.value("createDate").toLongLong();
        QString content = query.value("content").toString();
        this->insertHtml(content,1);
    }
}
//插入聊天
void ChatWidget::insertHtml(const QString &message,int orientation)
{

    ChatCell *chatCell = new ChatCell();
    chatCell->showInfo();

    qDebug() << "text" << chatCell->size();

//    QListWidgetItem *item = new QListWidgetItem();
//    item->setSizeHint(QSize(0, chatCell->size().height()));

    if (orientation == 1){
        //在最上面添加
        listWidget->insertItem(0,message);
        //listWidget->setItemWidget(item,chatCell);
    }
    else{
        //新消息添加到最后
        listWidget->addItem(message);
        //listWidget->setItemWidget(item,chatCell);
        listWidget->scrollToBottom();
    }
}

//发送信息
void ChatWidget::_q_send()
{
    qDebug()<<"_q_send" << user;

    QString text = sendText->toPlainText();
    if(text.trimmed().isEmpty())
        return;

    //显示数据
    insertHtml(text);

    //保存数据
    QString messageID = QXmppUtils::generateRandomBytes(12);
    QString username = XmppManager::getMyUsername();
    long long createDate = QDateTime::currentDateTime().toTime_t()*1000.0;
    SQLMsgHistory::insertBodyMessageByBody(text,
                                           messageID,
                                           this->user,
                                           username,
                                           XXEnum::XXMessageSendSending,
                                           createDate,
                                           this->chatType,
                                           false);
    //生成jid格式
    QString toJid = user;
    toJid = Utils::userToJid(toJid);
    XmppManager::getClient()->sendMessage(toJid,sendText->toPlainText());
    sendText->clear();
}

ChatWidget::~ChatWidget()
{
    ViewManager::showChat(this->user,false);

    delete      sendText;
    delete      sendButton;
    delete      rootLayout;
}
