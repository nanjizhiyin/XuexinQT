#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "QtGui"
#include <QXmppClient.h>

class QXmppIq;
class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
private:
    //读取账号信息
    void getMember();
private:
    QLabel      *usernameLabel;
    QLineEdit   *usernameLine;
    QLabel      *passwordLabel;
    QLineEdit   *passwordLine;

    QPushButton *registeButton;
    QPushButton *loginButton;

signals:

private slots:
    void _q_login();
    //注册
    void _q_register();

};

#endif // LOGIN_H
