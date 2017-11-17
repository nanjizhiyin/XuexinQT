#ifndef FRIENDWIDGET_H
#define FRIENDWIDGET_H

#include <QWidget>

class QScrollArea;
class QFrame;
class QVBoxLayout;

class FriendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FriendWidget(QWidget *parent = 0);

    QScrollArea  *mScroll;
    QVBoxLayout     *mListLayout;

signals:

public slots:
    void roster();
};

#endif // FRIENDWIDGET_H
