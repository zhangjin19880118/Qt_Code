#include "stone.h"
#include <QPoint>
#include <QString>
#include <QDebug>

Stone::Stone():d(Util::d)
{

}

void Stone::drawStone(QPainter &p,int selectId)
{
    if(this->mDeath)
        return;

    QPoint center=Util::getStonePoint(this->mRow,this->mCol);
    p.setPen(Qt::black);
    if(this->mStoneId==selectId)
        p.setBrush(Qt::gray);
    else
        p.setBrush(Qt::yellow);
    p.drawEllipse(center,d/2,d/2);

    QString strStone="帅仕相车马炮兵将士象车马炮卒";

    int index=7*(this->mStoneId>=16)+(int)(this->type);
    QChar ch=strStone.at(index);
    p.setFont(QFont("宋体",d/2));
    if(this->mStoneId<16)
        p.setPen(Qt::red);
    else
        p.setPen(Qt::black);
    p.drawText(Util::getStoneRect(this->mRow,this->mCol),Qt::AlignCenter,QString(ch));
}
