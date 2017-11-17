#ifndef MOREWIDGET_H
#define MOREWIDGET_H

#include <QWidget>

class MoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MoreWidget(QWidget *parent = 0);

signals:

public slots:

private slots:
    void _q_quitlogin();

};

#endif // MOREWIDGET_H
