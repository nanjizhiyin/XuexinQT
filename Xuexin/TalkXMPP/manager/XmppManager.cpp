#include "xmppmanager.h"
#include "Utils.h"

static QXmppClient *xmppClient = NULL;

static QString  kUsername = NULL;
static QString  kPassword = NULL;

XmppManager::XmppManager()
{
}
//得到connect
QXmppClient *XmppManager::getClient()
{
    if(xmppClient == NULL){
        xmppClient = new QXmppClient();
        xmppClient->logger()->setLoggingType(QXmppLogger::StdoutLogging);
    }
    return xmppClient;
}
//登录
void XmppManager::login(QString& username, QString& password)
{
    kUsername = username;
    kPassword = password;

    //生成jid格式
    username = Utils::userToJid(username);

    XmppManager::getClient();
    QXmppConfiguration configuration;
    configuration.setJid(username);
    configuration.setPassword(password);
    configuration.setDomain(XMPP_DOMAIN);
    configuration.setHost(XMPP_HOST);
    configuration.setResource(XMPP_RESOURCE);
    configuration.setPort(XMPP_POST);
    configuration.setKeepAliveTimeout(10);

    xmppClient->connectToServer(configuration,QXmppPresence());
}

//我的vcard
QString XmppManager::getMyUsername()
{
    return kUsername;
}
//
QString XmppManager::getMyPassword()
{
    return kPassword;
}
