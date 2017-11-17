#include "FriendCell.h"
#include "Utils.h"
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "ViewManager.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


FriendCell::FriendCell(QWidget *parent) :
    QPushButton(parent)
{

    this->setAutoFillBackground(true);
    this->setStyleSheet("background-color: rgb(19,253,123);");


    connect(this, SIGNAL(released()), this, SLOT(_q_openchat()));

    mLogo = new QLabel(this);
    mLogo->setFixedSize(QSize(40,40));

    mName = new QLabel(this);
    mName->setFixedHeight(20);

    mSignature   = new QLabel(this);
    mSignature->setFixedHeight(10);

    QFont font;
    font.setPointSize(10);
    mSignature->setFont(font);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    mSignature->setPalette(pe);

    mRootLayout = new QGridLayout(this);
    mRootLayout->setMargin(1);
    mRootLayout->setSpacing(0);
    mRootLayout->addWidget(mLogo,0,0,2,1);
    //mRootLayout->addSpacing(5);//添加20水平宽度的空白 b类型 垂直方向
    //rootLayout->addStretch(10);// 添加一个固定长度的延伸
    mRootLayout->addWidget(mName,0,1,1,1);
    mRootLayout->addWidget(mSignature,1,1,1,1,Qt::AlignCenter | Qt::AlignLeft);
}
//显示图片
void FriendCell::showAvatar(QString &avatar)
{

    //获取网络图片
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(avatar)));
}

void FriendCell::replyFinished(QNetworkReply *reply)
{
    QNetworkReply::NetworkError error =   reply->error();
    if(error == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap currentPicture;
        currentPicture.loadFromData(reply->readAll());

        QPixmap imgScaled;
        imgScaled = currentPicture.scaled(40,40,Qt::KeepAspectRatio);

        mLogo->setPixmap(imgScaled);
    }
    else{
        QImage iconFile(":/icon/icon114.png");
        QImage imgScaled;
        imgScaled = iconFile.scaled(40,40,Qt::KeepAspectRatio);

        mLogo->setPixmap(QPixmap::fromImage(imgScaled));
    }
}

//打开聊天窗口
void FriendCell::_q_openchat()
{
    qDebug()<<myJid;
    ViewManager::showChat(myJid,true);
}
