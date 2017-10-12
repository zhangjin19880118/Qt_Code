#include "mysubwidget.h"

MySubWidget::MySubWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle("子窗口");
    this->resize(800,600);
    b1.setParent(this);
    b1.move(100,100);
    b1.setText("切换到主窗口");
    this->connect(&b1,&QPushButton::released,this,&MySubWidget::sendSingal);
}

void MySubWidget::sendSingal()
{
    emit this->MySingal();
    emit this->MySingal(250,"我是子窗口");
}

