#include "mainwindow.h"
#include "LoginWidget.h"
#include "QXmppClient.h"
#include "SQLManager.h"
#include <QSqlQuery>
#include "ViewManager.h"
#include <qmessagebox.h>
#include "RootWidget.h"
#include "XmppManager.h"
#include "qgridlayout.h"
#include "QXmppRosterManager.h"
#include "QXmppUtils.h"
#include "SQLMember.h"
#include "SQLFriend.h"
#include "SignalManager.h"
#include <QSqlError>
#include "QXmppRosterIq.h"
#include "QXmppMessage.h"
#include "SQLMsgHistory.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //this->setFixedSize(300,600);

    setMinimumSize(300, 600);

    ViewManager::setMainWindow(this);

    mLoginWidget = NULL;
    mRootWidget = NULL;

    isDisconnectFromServer = false;
    //数据初始化
    SQLManager::init();

    //绑定xmpp
    xmppClient = XmppManager::getClient();
    connect(xmppClient,SIGNAL(connected()),this,SLOT(connected()));
    connect(xmppClient,SIGNAL(disconnected()),SLOT(disconnected()));
    connect(xmppClient,SIGNAL(error(QXmppClient::Error)),SLOT(error(QXmppClient::Error)));
    connect(xmppClient,SIGNAL(presenceReceived(QXmppPresence)),this,SLOT(presenceReceived(QXmppPresence)));
    connect(xmppClient,SIGNAL(messageReceived(QXmppMessage)),this,SLOT(messageReceived(QXmppMessage)));

    rosterManager = &xmppClient->rosterManager();
    connect(rosterManager,SIGNAL(subscriptionReceived(QString)),SLOT(subscriptionReceived(QString)));
    connect(rosterManager, SIGNAL(presenceChanged(QString,QString)),SLOT(presenceChanged(QString,QString)));
    connect(rosterManager, SIGNAL(rosterReceived()),SLOT(rosterReceived()));
    connect(rosterManager,SIGNAL(subscriptionReceived(QString)),SLOT(subscriptionReceived(QString)));
    connect(rosterManager,SIGNAL(itemRemoved(QString)),SLOT(itemRemoved(QString)));
    connect(rosterManager,SIGNAL(itemAdded(QString)),SLOT(itemAdded(QString)));
    connect(rosterManager,SIGNAL(itemChanged(QString)),SLOT(itemChanged(QString)));

    //验证账号和密码
    QString username;
    QString password;
    QSqlQuery query = SQLMember::selectUsers();
    if (query.next()){
        username = query.value(1).toString();
        password = query.value(2).toString();
    }
    if (password.isEmpty()){
        //显示登录
        this->showLogin(true);
    }else{
        //显示主界面
        this->showRoot(true);
        XmppManager::login(username,password);
    }

}
void MainWindow::itemChanged(const QString& jid)
{
    qDebug()<<"itemChanged="<<jid;
}
void MainWindow::itemAdded(const QString& jid)
{
    qDebug()<<"itemAdded="<<jid;
}
void MainWindow::itemRemoved(const QString& jid)
{
    qDebug()<<"removedJID="<<jid;
}
void MainWindow::subscriptionReceived(const QString& jid)
{
    qDebug()<<"subscriptionReceived"<<jid;
}

void MainWindow::presenceReceived(const QXmppPresence &presence)
{
    qDebug()<<"presenceReceived jid ="<<presence.from();
    if(presence.type() == presence.Subscribe){//好友请求关注我
        QMessageBox::StandardButton rb = QMessageBox::information(NULL, tr("好友请求"), presence.from()+tr("\n想关注你"),QMessageBox::Ok | QMessageBox::Cancel);
        if(rb == QMessageBox::Ok){
            //QXMPPManager::getClient()->rosterManager().acceptSubscription(presence.from(),tr("很高兴认识你"));
        }else{
            //QXMPPManager::getClient()->rosterManager().acceptSubscription(presence.from(),tr("不想加你"));
        }
    }else if(presence.type() == presence.Unsubscribe){//好友取消了关注我
        QMessageBox::information(NULL, tr("好友"), presence.from()+tr("\n取消了对我的关注"));
    }

}
//读完了好友列表
void MainWindow::rosterReceived()
{
    QVariantList uids;//用户ID
    QVariantList subs;//用户关系 both,none

    QVariantList avatars;//头像
    QVariantList names;//用户名
    QVariantList nicks;//备注
    QVariantList signatures;//备注

    //读取好友列表
    QStringList list = rosterManager->getRosterBareJids();
    for(int i = 0; i < list.size(); ++i)
    {
        QString jid = list.at(i);
        QXmppRosterIq::Item item = rosterManager->getRosterEntry(jid);

        //
        QXmppRosterIq::Item::SubscriptionType sub = item.subscriptionType();
        if (sub == QXmppRosterIq::Item::Both || sub == QXmppRosterIq::Item::To){
            subs << sub;
        }else{
            return;
        }

        //
        QString user = QXmppUtils::jidToUser(jid);
        uids << user;

        //
        QString name = item.name();
        names << name;

        //
        QString nick = item.nick();
        nicks << nick;

        //
        QString avatar = item.avatar();
        avatars << avatar;

        //
        QString signature = item.signature();
        signatures << signature;

    }
    //
    QString user = NULL;
    SQLFriend::deleteFriend(user);
    SQLFriend::deleteFriendInfo(user);

    //
    QSqlQuery query = SQLManager::getQuery();
    //批量插入数据 XS_UserProfile
    query.prepare("INSERT INTO XS_FriendList(uid,subscription) VALUES(?, ?)");
    query.addBindValue(uids);
    query.addBindValue(subs);

    if (!query.execBatch())
        qDebug() << query.lastError();


    //批量插入数据 XS_UserProfile
    query = SQLManager::getQuery();
    query.prepare("INSERT INTO XS_UserProfile(uid,name,nick,avatar,signature) VALUES(?, ?, ?, ?,?)");
    query.addBindValue(uids);
    query.addBindValue(names);
    query.addBindValue(nicks);
    query.addBindValue(avatars);
    query.addBindValue(signatures);

    if (!query.execBatch())
        qDebug() << query.lastError();

    emit SignalManager::sharedManager().signal_roster();
}

void MainWindow::presenceChanged(const QString& bareJid,const QString& resource)
{
    qDebug("example_2_rosterHandling:: Presence changed %s/%s", qPrintable(bareJid), qPrintable(resource));
}
void MainWindow::messageReceived(const QXmppMessage &message)
{
    //收到新消息
    qDebug()<<"messageReceived";

    //告诉服务器我收到了
    QXmppElement recvEle;
    recvEle.setTagName("received");
    recvEle.setAttribute("xmlns","xuexin:xmpp:receipts");
    recvEle.setAttribute("id",message.id());
    QXmppElementList eleList;
    eleList.append(recvEle);

    QXmppMessage recvMessage;
    recvMessage.setTo(message.from());
    recvMessage.setType(QXmppMessage::Normal);
    recvMessage.setExtensions(eleList);

    //告诉服务器我收到了
    xmppClient->sendPacket(recvMessage);

    //保存数据
    SQLMsgHistory::insertMessage(message);

    //
    QString chatID = QXmppUtils::jidToUser(message.from());
    ViewManager::showChat(chatID,true);

    //处理界面
    QXmppMessage::Type type = message.type();
    if(type == QXmppMessage::Chat){
        //私人聊天
    }
    else if(type == QXmppMessage::Headline){
        //公众号
    }
    else if(type == QXmppMessage::GroupChat){
        //讨论组
    }
    else if(type == QXmppMessage::Normal){
        //对方收到消息了

    }
    else if(type == QXmppMessage::Error){
        //消息发送失败

    }
    emit SignalManager::sharedManager().signal_recvMessage(message);
}
//获取离线消息
void MainWindow::getOfflineMessage()
{

    //告诉服务器我收到了
    QXmppElement eleoffline;
    eleoffline.setTagName("offline");
    eleoffline.setAttribute("xmlns","http://jabber.org/protocol/offline");
    eleoffline.setAttribute("id","fadsfadfasdfad");

    QXmppElement elexfield;
    elexfield.setTagName("fetch");
    eleoffline.appendChild(elexfield);

    QXmppElementList eleList;
    eleList.append(eleoffline);

    QXmppIq iq;
    iq.setType(QXmppIq::Get);
    iq.setExtensions(eleList);

    //告诉服务器我收到了
    xmppClient->sendPacket(iq);
}

void MainWindow::connected()
{
    isDisconnectFromServer = false;
    qDebug() << "登录成功";

    QString username = XmppManager::getMyUsername();
    QString password = XmppManager::getMyPassword();

    //保存账号和密码
    SQLMember::deleteAllUserAndPassword();
    SQLMember::saveUserAndPassword(username,password);

    //打开数据库
    SQLManager::openDB(username);

    //显示界面
    this->showRoot(true);

    //获取离线消息
    this->getOfflineMessage();
}
void MainWindow::disconnected()
{
    if (isDisconnectFromServer){
        this->showLogin(true);
        qDebug() << "主动退出";
    }
    else{
        qDebug() << "掉线了";
        QMessageBox::warning(this, tr("错误"), tr("登录失败"));
    }
    isDisconnectFromServer = false;
}
void MainWindow::error(QXmppClient::Error)
{
    qDebug() << "登录错误";
    this->showLogin(true);
}




//打开登录
void MainWindow::showLogin(bool b)
{
    if(b){
        this->showRoot(false);
        if(mLoginWidget == NULL){
            mLoginWidget = new LoginWidget(this);
            qDebug() << "kLoginWidget->show()";
            mLoginWidget->show();
        }
    }else{
        if(mLoginWidget != NULL){
            qDebug() << "delete kLoginWidget";
            delete mLoginWidget;
            mLoginWidget = NULL;
        }
    }
}
//打开主界面
void MainWindow::showRoot(bool b)
{
    if(b){
        this->showLogin(false);
        if(!mRootWidget){
            mRootWidget = new RootWidget(this);
            qDebug() << "kRootWidget->show()";

            mRootWidget->show();
        }
    }else{
        if(mRootWidget != NULL){
            qDebug() << "delete mRootWidget";
            delete mRootWidget;
            mRootWidget = NULL;
        }
    }
}
//获取主界面
RootWidget& MainWindow::getRootWidget()
{
    return *mRootWidget;
}

void MainWindow::disconnectFromServer()
{
    qDebug() << "disconnectFromServer";
    SQLMember::deleteAllUserAndPassword();
    isDisconnectFromServer = true;
    xmppClient->disconnectFromServer();
}
MainWindow::~MainWindow()
{
}
