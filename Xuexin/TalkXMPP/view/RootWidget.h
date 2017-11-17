#ifndef ROOTWIDGET_H
#define ROOTWIDGET_H

#include <QWidget>

class QTabWidget;

class RootWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RootWidget(QWidget *parent = 0);

private:
    QTabWidget  *mTabWidget;

signals:

public slots:

};

#endif // ROOTWIDGET_H
