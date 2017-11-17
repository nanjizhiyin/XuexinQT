#ifndef CHATCELL_H
#define CHATCELL_H

#include <QWidget>

class QVBoxLayout;
class QLabel;
class QTextEdit;

class ChatCell : public QWidget
{
    Q_OBJECT
public:
    explicit ChatCell(QWidget *parent = 0);
    ~ChatCell();

    QVBoxLayout  *rootLayout;
    QLabel      *dateLabel;//时间
    QTextEdit      *contentLabel;//内容

    //设置信息
    void showInfo();
signals:

public slots:
};

#endif // CHATCELL_H
