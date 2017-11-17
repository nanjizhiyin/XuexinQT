#ifndef XMPPMANAGER_H
#define XMPPMANAGER_H
#include <QObject>

#define XMPP_HTTP    "http://im.xuexin.co/"
#define XMPP_DOMAIN  "im.xuexin.co"
#define XMPP_HOST    "im.xuexin.co"
#define XMPP_RESOURCE "mac"
#define XMPP_POST     5222

class QXmppClient;
class QXmppVCardIq;
class XmppManager
{
public:
    XmppManager();
    //得到connect
    static QXmppClient *getClient();

    //登录
    static void login( QString &username, QString &password);

    //s
    static QString getMyUsername();
    //
    static QString getMyPassword();
};

#endif // XMPPMANAGER_H
