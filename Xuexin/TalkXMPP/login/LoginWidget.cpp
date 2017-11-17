#include "LoginWidget.h"
#include "XmppManager.h"
#include "Utils.h"
#include "QXmppClient.h"
#include "ViewManager.h"
#include "mainwindow.h"
#include "SQLManager.h"
#include "SQLMember.h"
#include <qsqlquery.h>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("XPFIRST"));
    setMinimumSize(300, 600);


    int x = 20;
    int y = 100;

    usernameLabel = new QLabel(tr("用户名:"),this);
    usernameLabel->setGeometry(x, y, 50, 20);
    usernameLine = new QLineEdit(this);
    usernameLine->setGeometry(x+50,y,180,20);
    usernameLine->setText("101002");
    y += 30;
    passwordLabel = new QLabel(tr(" 密码:"),this);
    passwordLabel->setGeometry(x, y, 50, 20);
    passwordLine = new QLineEdit(this);
    passwordLine->setGeometry(x+50,y,180,20);
    passwordLine->setText("123456");


    x = 50;
    y += 30;
    registeButton = new QPushButton(this);
    registeButton->setGeometry(x,y,100,20);
    registeButton->setText(tr("注册"));

    loginButton = new QPushButton(this);
    loginButton->setGeometry(x+110,y,100,20);
    loginButton->setText(tr("登录"));

    connect(loginButton, SIGNAL(released()), this, SLOT(_q_login()));
    connect(registeButton, SIGNAL(released()), this, SLOT(_q_register()));

    getMember();
}
//读取账号信息
void LoginWidget::getMember()
{
    QSqlQuery query = SQLMember::selectUsers();
    if (query.next()){
        QString username = query.value(1).toString();
        QString password = query.value(2).toString();
        usernameLine->setText(username);
        passwordLine->setText(password);
    }
}
//登录
void LoginWidget::_q_login()
{
    qDebug() << "开始登录";
    QString username = usernameLine->text();
    QString password = passwordLine->text();

    username = Utils::escapeNode(username);

    XmppManager::login(username,password);
}
//注册
void LoginWidget::_q_register()
{
}

LoginWidget::~LoginWidget()
{
    delete      usernameLabel;
    delete      usernameLine;
    delete      passwordLabel;
    delete      passwordLine;

    delete      registeButton;
    delete      loginButton;
}

