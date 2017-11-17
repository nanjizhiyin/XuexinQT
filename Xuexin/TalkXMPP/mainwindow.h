#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmppClient.h>

class LoginWidget;
class RootWidget;
class QXmppClient;
class QXmppRosterManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //打开登录
    void showLogin(bool b);
    //打开主界面
    void showRoot(bool b);
    //获取主界面
    RootWidget& getRootWidget();

    //主动退出登录
    bool        isDisconnectFromServer;//主动退出登录
    void        disconnectFromServer();
private:
    LoginWidget *mLoginWidget;
    RootWidget *mRootWidget;

    QXmppClient *xmppClient;
    QXmppRosterManager *rosterManager;

private slots:
    //连接成功
    void connected();
    void disconnected();
    void error(QXmppClient::Error);

    void getOfflineMessage();//获取离线消息

    void messageReceived(const QXmppMessage &message);
    void presenceChanged(const QString& bareJid,const QString& resource);
    void rosterReceived();
    void subscriptionReceived(const QString& bareJid);
    void presenceReceived(const QXmppPresence &presence);
    void itemRemoved(const QString&);//取消关注
    void itemAdded(const QString&);//添加关注
    void itemChanged(const QString&);//改变关注
};

#endif // MAINWINDOW_H
