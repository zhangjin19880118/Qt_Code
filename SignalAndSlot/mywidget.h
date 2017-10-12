#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<mysubwidget.h>

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = 0);
    ~MyWidget();
    void MySlot();
    void dealSubWin();
    void dealsubSlot(int,QString);
private:
    MySubWidget w;
    QPushButton b;
};

#endif // MYWIDGET_H
