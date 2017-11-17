#include "RootWidget.h"
#include <QTableWidget>
#include "InfoWidget.h"
#include "FriendWidget.h"
#include "GroupWidget.h"
#include "SNSWidget.h"
#include "qgridlayout.h"
#include "MoreWidget.h"

RootWidget::RootWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(parent->minimumSize());

    QGridLayout *rootLayout = new QGridLayout(this);
    rootLayout->setContentsMargins(0,0,0,0);//设置布局内部四边的空隙

    mTabWidget = new QTabWidget();
    //mTabWidget->addTab(new InfoWidget(mTabWidget),trUtf8("学信"));
    mTabWidget->addTab(new FriendWidget(mTabWidget),trUtf8("通讯录"));
    mTabWidget->addTab(new GroupWidget(mTabWidget),trUtf8("讨论组"));
    mTabWidget->addTab(new MoreWidget(mTabWidget),trUtf8("设置"));
    //mTabWidget->setCurrentIndex(1);

    rootLayout->addWidget(mTabWidget);

}
