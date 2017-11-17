#include "SignalManager.h"


static SignalManager *instance;

SignalManager::SignalManager(QObject *parent) :
    QObject(parent)
{
}

SignalManager& SignalManager::sharedManager()
{
    if (instance == NULL)
    {
        instance = new SignalManager();
    }
    return *instance;
}
