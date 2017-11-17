#include "MoreWidget.h"
#include "ViewManager.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "mainwindow.h"

MoreWidget::MoreWidget(QWidget *parent) :
    QWidget(parent)
{

    QPushButton *quitButton = new QPushButton(this);
    quitButton->setFixedHeight(40);
    quitButton->setText(tr("退出"));
    connect(quitButton, SIGNAL(released()), this, SLOT(_q_quitlogin()));

    QVBoxLayout *rootLayout = new QVBoxLayout(this);
    rootLayout->setMargin(1);
    rootLayout->addWidget(quitButton);
}

void MoreWidget::_q_quitlogin()
{
    ViewManager::getMainWindow()->disconnectFromServer();
}
