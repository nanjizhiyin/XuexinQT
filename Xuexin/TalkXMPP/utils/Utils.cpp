#include "Utils.h"
#include "QtGui"

Utils::Utils()
{
}
QString  Utils::escapeNode(QString &string)
{
    if(string != NULL){
        string = string.trimmed();
        string = string.replace('"',"\\22");
        string = string.replace("&","\\26");
        string = string.replace("\'","\\27");
        string = string.replace("/","\\2f");
        string = string.replace(":","\\3a");
        string = string.replace("<","\\3c");
        string = string.replace(">","\\3e");
        string = string.replace("@","\\40");
        //string = string.replace("\\","\\5c");
    }
    return string;
}
QString  Utils::unescapeNode(QString &string)
{
    if(string != NULL){
        string = string.trimmed();
        string = string.replace("\\22",QChar('"'));
        string = string.replace("\\26","&");
        string = string.replace("\\27","\'");
        string = string.replace("\\2f","/");
        string = string.replace("\\3a",":");
        string = string.replace("\\3c","<");
        string = string.replace("\\3e",">");
        string = string.replace("\\40","@");
        //string = string.replace("\\","\\5c");
    }
    return string;
}
//user to jid
QString  Utils::userToJid(QString &user)
{
    QString myjid = user;
    myjid.append(QString("@")+XMPP_DOMAIN+QString("/")+XMPP_RESOURCE);
    return myjid;
}
//验证密码
bool Utils::isPassword(QString &password){
    qDebug()<<password;
    QRegExp validInputValRegEx("^[0-9a-zA-z_]{6,}$");//至少6位由数字、26个英文字母或者下划线组成的字符串
    QRegExpValidator *v = new QRegExpValidator(validInputValRegEx);
    int pos =0;
    QValidator::State result = v->validate(password,pos);
    if(result == QValidator::Acceptable)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//验证邮箱格式
bool    Utils::isEmail(QString &email)
{
    QRegExp validInputValRegEx("[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}");
    QRegExpValidator *v = new QRegExpValidator(validInputValRegEx);
    int pos =0;
    QValidator::State result = v->validate(email,pos);
    if(result == QValidator::Acceptable)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//由图片名字得到路径
QString Utils::getImageURLWithFileNmae(QString &imageName)
{
    if (imageName.isEmpty()) {
        return imageName;
    }
    if (imageName.indexOf('http') >= 0){
        return imageName;
    }
    QStringList imageNames=imageName.split("@");
    if (imageNames.length() >= 2) {
        imageName = "http://" + imageNames.at(0)  + ".xuexin.org.cn/" + imageNames.at(1);
    }
    return imageName;
}
