#ifndef FRIENDCELL_H
#define FRIENDCELL_H

class QXmppVCardIq;
class QLabel;
class QGridLayout;
class QPushButton;
class QLabel;
class QNetworkReply;

#include <QPushButton>

class FriendCell : public QPushButton
{
    Q_OBJECT
public:
    explicit FriendCell(QWidget *parent = 0);
    QGridLayout *mRootLayout;
    QLabel      *mLogo;
    QLabel      *mName;
    QLabel      *mSignature;
    QString myJid;

    //显示图片
    void showAvatar(QString &avatar);
signals:
    
public slots:
    void replyFinished(QNetworkReply *reply);

private slots:
    //打开聊天窗口
    void _q_openchat();
};

#endif // FRIENDCELL_H
