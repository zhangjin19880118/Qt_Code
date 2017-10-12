#include "mywidget.h"
#include <QDebug>
#include "mybutton.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->move(100,100);
    this->setWindowTitle("主窗口");
    this->resize(800,600);

    b.setParent(this);
    b.move(50,50);
    b.setText("切换到子窗口");

    this->connect(&b,&QPushButton::pressed,this,&MyWidget::MySlot);
    void (MySubWidget::*singal1)()=&MySubWidget::MySingal;
    this->connect(&w,singal1,this,&MyWidget::dealSubWin);
    void (MySubWidget::*singal2)(int,QString)=&MySubWidget::MySingal;
    this->connect(&w,singal2,this,&MyWidget::dealsubSlot);

    QPushButton *b2=new QPushButton(this);
    b2->move(200,200);
    b2->setText("Lambda表达式");
    this->connect(b2,&QPushButton::clicked,
    [=](bool isCheck)
    {
        qDebug()<<isCheck;
    }
    );

    MyButton *b3=new MyButton(this);
    b3->setText("自定义按钮");
    this->connect(b3,&MyButton::released,
    [=]()
    {
        qDebug()<<"我是自定义按钮";
    }
    );
}

void MyWidget::MySlot()
{
    this->hide();
    w.show();
}

void MyWidget::dealSubWin()
{
    this->show();
    w.hide();
}

void MyWidget::dealsubSlot(int num,QString str)
{
    qDebug()<<num<<str;
}

MyWidget::~MyWidget()
{

}
