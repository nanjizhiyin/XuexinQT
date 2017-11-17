#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include "QXmppClient.h"
#include "QXmppLogger.h"
#include <QXmppUtils.h>
#include <QXmppVCardIq.h>
#include "QXmppRosterManager.h"
#include <iostream>
#include <QXmppVCardManager.h>
#include "qregexp.h"
#include <QXmppMessage.h>
#include <QXmppVCardIq.h>
#include "XmppManager.h"
#include <QXmppIq.h>


class Utils
{
public:
    Utils();
    static QString  escapeNode(QString &string);
    static QString  unescapeNode(QString &string);
    static QString  userToJid(QString &user);
    //验证邮箱格式
    static bool    isEmail(QString &email);
    //验证密码
    static bool isPassword(QString &password);
    //由图片名字得到路径
    static  QString getImageURLWithFileNmae(QString &imageName);
};

#endif // UNIT_H
