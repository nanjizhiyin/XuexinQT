#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#include <QObject>
#include "QXmppMessage.h"

class SignalManager : public QObject
{
    Q_OBJECT
public:
    explicit SignalManager(QObject *parent = 0);

    static SignalManager& sharedManager();
signals:
    //好友列表更新了
    void signal_roster();

    //收到新消息
    void signal_recvMessage(const QXmppMessage &message);

public slots:

};

#endif // SIGNALMANAGER_H
