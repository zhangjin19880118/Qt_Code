#include "util.h"

int Util::d=80;

Util::Util()
{

}

QPoint Util::getStonePoint(int row, int col)
{
    int x=col*d+d;
    int y=row*d+d;
    return QPoint(x,y);
}

QRect Util::getStoneRect(int row, int col)
{
    QPoint center=Util::getStonePoint(row,col);
    center -=QPoint(d/2,d/2);
    return QRect(center.x(),center.y(),d,d);
}

bool Util::getPlatePoint(QPoint pt, int &row, int &col)
{
    int t[]={-1,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9};
    int rowIndex=pt.y()/(d/2);
    int colIndex=pt.x()/(d/2);

    if(0==rowIndex)
        return false;
    if(0==colIndex)
        return false;
    if(rowIndex>20)
        return false;
    if(colIndex>18)
        return false;
    row=t[rowIndex];
    col=t[colIndex];
    return true;
}
