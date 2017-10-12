#include "mywidget.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    this->resize(800,600);

    this->edit1=new QLineEdit(this);
    this->edit1->setPlaceholderText("姓名");

    this->edit2=new QLineEdit(this);
    this->edit2->setPlaceholderText("性别");
    this->edit2->move(0,50);

    this->edit3=new QLineEdit(this);
    this->edit3->setPlaceholderText("年龄");
    this->edit3->move(0,100);

    this->edit4=new QLineEdit(this);
    this->edit4->setPlaceholderText("学号");
    this->edit4->move(0,150);

    this->button1=new QPushButton(this);
    this->button1->setText("保存");
    this->button1->move(0,200);

    this->connect(button1,&QPushButton::clicked,this,&MyWidget::OnClicked);

    this->button2=new QPushButton(this);
    this->button2->setText("读取");
    this->button2->move(100,200);
    this->connect(button2,&QPushButton::released,this,&MyWidget::OnReleased);
}

void MyWidget::OnClicked()
{
    QString str1=this->edit1->text();
    QString str2=this->edit2->text();
    QString str3=this->edit3->text();
    QString str4=this->edit4->text();

    QFile file("student.txt");
    file.open(QFile::WriteOnly);

    QDataStream ds(&file);
    ds<<str1<<str2<<str3<<str4;

    file.close();
}

void MyWidget::OnReleased()
{
    QString str1,str2,str3,str4;

    QFile file("student.txt");
    file.open(QFile::ReadOnly);

    QDataStream ds(&file);
    ds>>str1>>str2>>str3>>str4;

    this->edit1->setText(str1);
    this->edit2->setText(str2);
    this->edit3->setText(str3);
    this->edit4->setText(str4);

    file.close();
}
