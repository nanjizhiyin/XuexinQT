#include "chatcell.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <qdebug.h>
#include <QTextEdit>

ChatCell::ChatCell(QWidget *parent) : QWidget(parent)
{

}
//设置信息
void ChatCell::showInfo()
{
    //this->resize(300,1000);

    rootLayout = new QVBoxLayout(this);
    rootLayout->setSpacing(0);
    rootLayout->setMargin(0);

    dateLabel = new QLabel(this);
    dateLabel->setText("2015-01-26 11:23:45");
    dateLabel->adjustSize();
    rootLayout->addWidget(dateLabel);

    contentLabel = new QTextEdit();
    contentLabel->setFocusPolicy(Qt::NoFocus);
    contentLabel->resize(100,100);
//    contentLabel->setWordWrap(true);
//    contentLabel->setAlignment(Qt::AlignTop);

    contentLabel->setText("GHqgr");

    qDebug() << "text12111" <<contentLabel->size();
    contentLabel->adjustSize();
    qDebug() << "text12111" <<contentLabel->size();

    rootLayout->addWidget(contentLabel);

    qDebug() << "text12" <<contentLabel->size();
    qDebug() << "text11" << rootLayout->sizeHint();

    this->resize(300,60);
    //this->resize(300,rootLayout->sizeHint().height());
}
//设置名称

ChatCell::~ChatCell()
{

}

