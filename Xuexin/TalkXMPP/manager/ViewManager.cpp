#include "ViewManager.h"
#include "loginwidget.h"
#include "mainwindow.h"
#include "ChatWidget.h"

static MainWindow *kMainWindow = NULL;
static QSystemTrayIcon *kTrayIcon = NULL;

static  QStringList chattingList;//已经打开的聊天窗口

ViewManager::ViewManager()
{
}

void ViewManager::setMainWindow(MainWindow *mainWindow)
{
    kMainWindow = mainWindow;
}
//返回主窗口
MainWindow *ViewManager::getMainWindow()
{
    return kMainWindow;
}
//显示icon
QSystemTrayIcon* ViewManager::showTrayIcon(const QString &title,const QString &msg)
{
    if(kTrayIcon == NULL){
        kTrayIcon = new QSystemTrayIcon();
        kTrayIcon->setIcon(QIcon(":/images/icon.png"));
        kTrayIcon->setToolTip("XPFirst made by Gaojindan");

    }
   kTrayIcon->show();
   kTrayIcon->showMessage(title,msg,QSystemTrayIcon::Information,10000);
   return kTrayIcon;
}

//打开聊天窗口
void ViewManager::showChat(const QString &jid,
                           bool b,
                           XXEnum::XXChatType chatType)
{
    if(b){
        if(chattingList.contains(jid)){
            //已经打开了
            return;
        }
        qDebug() << "打开" <<jid;
        chattingList<<jid;
        ChatWidget *chat = new ChatWidget();
        chat->setUser(jid);
        chat->show();
    }else{
        qDebug() << "关闭" <<jid;
        chattingList.removeOne(jid);
    }
}
