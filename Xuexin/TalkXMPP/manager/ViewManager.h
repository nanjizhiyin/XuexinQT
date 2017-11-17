#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H
#include <QtGui>
#include "QSystemTrayIcon"
#include "EnumManager.h"

class MainWindow;

class ViewManager
{
public:
    ViewManager();
    static void setMainWindow(MainWindow *mainWindow);
    static MainWindow *getMainWindow();

    //显示icon
    static QSystemTrayIcon* showTrayIcon(const QString &title,const QString &msg);

    //打开聊天窗口
    static void showChat(const QString &jid,
                         bool b = true,
                         XXEnum::XXChatType chatType = XXEnum::XXChatNone);
};

#endif // VIEWMANAGER_H
