#include "FriendWidget.h"
#include "SignalManager.h"
#include "qdebug.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QSqlQuery>
#include <QWidget>
#include <QLabel>
#include "SQLFriend.h"
#include "FriendCell.h"
#include "Utils.h"

FriendWidget::FriendWidget(QWidget *parent) :
    QWidget(parent)
{
    //this->setStyleSheet("background-color: rgb(12,23,123);");

    SignalManager *obj = &SignalManager::sharedManager();
    connect(obj,SIGNAL(signal_roster()),SLOT(roster()));

    QHBoxLayout *lay=new QHBoxLayout();
    setLayout(lay);//setting layout

    mScroll = new QScrollArea;
    mScroll->setBackgroundRole(QPalette::Dark);
    mScroll->setAutoFillBackground(true);
    mScroll->setWidgetResizable(true);
    lay->addWidget(mScroll);
    //mScroll->setGeometry(0,0,parent->size().width(),parent->size().height());

    QWidget *tmpWidget = new QWidget;
    mScroll->setWidget(tmpWidget);

    mListLayout = new QVBoxLayout(tmpWidget);
    mListLayout->setSpacing(14);
    mListLayout->setMargin(10);

}
void FriendWidget::roster()
{
    qDebug()<<"FriendWidget::roster";

    QSqlQuery query = SQLFriend::selectFriends();

    int size = 0;
    while (query.next()) {
        size += 1;

        QString uid = query.value(1).toString();
        QString nick = query.value(3).toString();
        if (nick.length() == 0){
            nick = query.value(2).toString();
        }
        //头像
        QString avatar = query.value(4).toString();
        avatar = Utils::getImageURLWithFileNmae(avatar);
        //心情
        QString signature = query.value(5).toString();

        qDebug()<<"signature"<<signature;

        FriendCell *friendCell = new FriendCell;
        friendCell->setFixedHeight(50);
        //friendCell->setFixedWidth(270);
        friendCell->myJid = uid;
        friendCell->mName->setText(nick);
        friendCell->mSignature->setText(signature);
        friendCell->showAvatar(avatar);

        mListLayout->addWidget(friendCell);


    }
    qDebug()<<size;
}
