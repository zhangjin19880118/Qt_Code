#ifndef MYSUBWIDGET_H
#define MYSUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class MySubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MySubWidget(QWidget *parent = 0);
    void sendSingal();
signals:
    void MySingal();
    void MySingal(int,QString);
public slots:
private:
    QPushButton b1;
};

#endif // MYSUBWIDGET_H
