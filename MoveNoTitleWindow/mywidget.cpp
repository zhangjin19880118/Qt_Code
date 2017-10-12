#include "mywidget.h"
#include <QCursor>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    this->mOriginMousePoint = QCursor::pos();
    qDebug()<<this->mOriginMousePoint;
    qDebug()<<this->pos();
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    this->mNewMousePoint=QCursor::pos();
    QPoint delta=this->mNewMousePoint-this->mOriginMousePoint;
    this->move(this->pos()+delta);
    this->mOriginMousePoint = this->mNewMousePoint;
}
