#include "board.h"
#include <QPainter>
#include <QPoint>
#include <QDebug>

Board::Board(QWidget *parent) : QWidget(parent),d(Util::d)
{
    struct{
        Stone::Type type;
        int row;
        int col;
    }p[16]=
    {
        {Stone::Che,9,8},
        {Stone::Ma,9,7},
        {Stone::Xiang,9,6},
        {Stone::Shi,9,5},
        {Stone::Shuai,9,4},
        {Stone::Che,9,0},
        {Stone::Ma,9,1},
        {Stone::Xiang,9,2},
        {Stone::Shi,9,3},
        {Stone::Pao,7,1},
        {Stone::Pao,7,7},
        {Stone::Bing,6,0},
        {Stone::Bing,6,2},
        {Stone::Bing,6,4},
        {Stone::Bing,6,6},
        {Stone::Bing,6,8}
    };
    for(int i=0;i<32;++i)
    {
        this->mStone[i].mDeath=false;
        this->mStone[i].mStoneId=i;
        if(i<16)
        {
            this->mStone[i].mRow=p[i].row;
            this->mStone[i].mCol=p[i].col;
            this->mStone[i].type=p[i].type;
        }
        else
        {
            this->mStone[i].mRow=9-p[i-16].row;
            this->mStone[i].mCol=8-p[i-16].col;
            this->mStone[i].type=p[i-16].type;
        }
    }
    this->selectId = -1;
    this->redTurn=true;
}

void Board::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    this->drawPlate(p);
    for(int i=0;i<32;++i)
    {
        this->mStone[i].drawStone(p,this->selectId);
    }
}

void Board::drawPlate(QPainter &p)
{
    for(int i=1;i<=10;++i)
        p.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    for(int i=1;i<=9;++i)
    {
        if(1==i||9==i)
             p.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        p.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
        p.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
    }

    p.drawLine(QPoint(4*d,d),QPoint(6*d,3*d));
    p.drawLine(QPoint(4*d,3*d),QPoint(6*d,d));

    p.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    p.drawLine(QPoint(4*d,10*d),QPoint(6*d,8*d));

    this->drawFlower(p,2,1);
    this->drawFlower(p,2,7);

    this->drawFlower(p,3,0);
    this->drawFlower(p,3,2);
    this->drawFlower(p,3,4);
    this->drawFlower(p,3,6);
    this->drawFlower(p,3,8);

    this->drawFlower(p,7,1);
    this->drawFlower(p,7,7);

    this->drawFlower(p,6,0);
    this->drawFlower(p,6,2);
    this->drawFlower(p,6,4);
    this->drawFlower(p,6,6);
    this->drawFlower(p,6,8);
}

void Board::drawFlower(QPainter &p,int row,int col)
{
    QPoint Origin;
    QPoint center=Util::getStonePoint(row,col);

    if(col!=8)
    {
        Origin=center+QPoint(d/6,-d/6);//1
        p.drawLine(Origin,Origin+QPoint(d/3,0));
        p.drawLine(Origin,Origin+QPoint(0,-d/3));

        Origin=center+QPoint(d/6,d/6);//4
        p.drawLine(Origin,Origin+QPoint(d/3,0));
        p.drawLine(Origin,Origin+QPoint(0,d/3));
    }

    if(col!=0)
    {
        Origin=center+QPoint(-d/6,-d/6);//2
        p.drawLine(Origin,Origin+QPoint(-d/3,0));
        p.drawLine(Origin,Origin+QPoint(0,-d/3));

        Origin=center+QPoint(-d/6,d/6);//3
        p.drawLine(Origin,Origin+QPoint(-d/3,0));
        p.drawLine(Origin,Origin+QPoint(0,d/3));
    }
}

void Board::mousePressEvent(QMouseEvent *event)
{
    if(Qt::RightButton==event->buttons())
        return;
    QPoint ptClick=event->pos();
    int row=-1,col=-1;
    if(!Util::getPlatePoint(ptClick,row,col))
        return;
    qDebug()<<row<<col;
    int clickId=this->getStoneId(row,col);
    if(-1==this->selectId)
    {
        this->selectStone(clickId);
    }
    else
    {
        if(clickId!=-1&&(clickId<16==selectId<16))
        {
            this->selectStone(clickId);
            return;
        }
        if(canMovesStone(this->selectId,clickId,row,col))
            this->moveStone(this->selectId,clickId,row,col);
    }
}

int Board::getStoneId(int row, int col)
{
    for(int i=0;i<32;++i)
    {
        if(this->mStone[i].mRow==row&&this->mStone[i].mCol==col&&!this->mStone[i].mDeath)
            return i;
    }
    return -1;
}

void Board::selectStone(int select)
{
    if(this->redTurn!=select<16)
        return;
    this->selectId=select;
    this->update();
}

void Board::moveStone(int select, int kill, int row, int col)
{
    this->mStone[select].mRow=row;
    this->mStone[select].mCol=col;
    if(kill!=-1)
        this->mStone[kill].mDeath=true;
    this->selectId=-1;
    this->redTurn=!this->redTurn;
    this->update();
}

bool Board::canMovesStone(int select, int kill, int row, int col)
{
    switch (this->mStone[select].type)
    {
    case Stone::Shuai:
        return this->canMoveShuai(select,kill,row,col);
        break;
    case Stone::Shi:
        return this->canMoveShi(select,kill,row,col);
        break;
    case Stone::Xiang:
        return this->canMoveXiang(select,kill,row,col);
        break;
    case Stone::Che:
        return this->canMoveChe(select,kill,row,col);
        break;
    case Stone::Ma:
        return  this->canMoveMa(select,kill,row,col);
        break;
    case Stone::Pao:
        return this->canMovePao(select,kill,row,col);
        break;
    case Stone::Bing:
        return this->canMoveBing(select,kill,row,col);
        break;
    default:
        break;
    }
    return false;
}

bool Board::canMoveShuai(int select, int kill, int row, int col)
{
    if(kill != -1 && this->mStone[kill].type == Stone::Shuai)
        return canMoveChe(select,kill,row,col);

    int dRow = qAbs(this->mStone[select].mRow - row);
    int dCol = qAbs(this->mStone[select].mCol - col);
    if(dRow + dCol != 1)
        return false;

    if(col < 3 || col > 5)
        return false;
    if(this->mStone[select].mStoneId < 16)
    {
        if(row < 7 || row > 9)
            return false;
    }
    else
    {
        if(row < 0 || row > 2)
            return false;
    }
    return true;
}

bool Board::canMoveShi(int select, int kill, int row, int col)
{
     if(col < 3 || col > 5)
         return false;
     if(this->mStone[select].mStoneId < 16)
     {
         if(row < 7 || row > 9)
             return false;
     }
     else
     {
         if(row < 0 || row > 2)
             return false;
     }

     int dRow = qAbs(this->mStone[select].mRow - row);
     int dCol = qAbs(this->mStone[select].mCol - col);
     if(dRow * 10 + dCol != 11)
         return false;
     return true;
}

bool Board::canMoveXiang(int select, int kill, int row, int col)
{
    if(this->mStone[select].mStoneId < 16)
    {
        if(row < 5)
            return false;
    }
    else
    {
        if(row > 4)
            return false;
    }

    int dRow = qAbs(this->mStone[select].mRow - row);
    int dCol = qAbs(this->mStone[select].mCol - col);
    if(dRow * 10 + dCol != 22)
        return false;

    int eRow = (this->mStone[select].mRow + row)/2;
    int eCol = (this->mStone[select].mCol + col)/2;
    int eye = getStoneId(eRow, eCol);
    if(eye != -1)
        return false;
    return true;
}

bool Board::canMoveChe(int select, int kill, int row, int col)
{
    int ret = getStoneCount(this->mStone[select].mRow, this->mStone[select].mCol, row, col);
    if(ret != 0)
        return false;
    return true;
}

bool Board::canMoveMa(int select, int kill, int row, int col)
{
    int dRow = qAbs(this->mStone[select].mRow - row);
    int dCol = qAbs(this->mStone[select].mCol - col);
    int d = dRow * 10 + dCol;
    if(d != 21 && d != 12)
        return false;

    if(d == 21)
    {
        int eRow = (this->mStone[select].mRow + row)/2;
        int eCol = this->mStone[select].mCol;
        if(getStoneId(eRow, eCol) != -1)
            return false;
    }
    else
    {
        int eRow = this->mStone[select].mRow;
        int eCol = (this->mStone[select].mCol + col)/2;
        if(getStoneId(eRow, eCol) != -1)
            return false;
    }
    return true;
}

bool Board::canMovePao(int select, int kill, int row, int col)
{
    if(kill == -1)
    {
        int ret = getStoneCount(this->mStone[select].mRow, this->mStone[select].mCol, row, col);
        if(ret != 0)
            return false;
    }
    else
    {
        int ret = getStoneCount(this->mStone[select].mRow, this->mStone[select].mCol, row, col);
        if(ret != 1)
            return false;
    }
    return true;
}

bool Board::canMoveBing(int select, int kill, int row, int col)
{
    int dRow = qAbs(this->mStone[select].mRow - row);
    int dCol = qAbs(this->mStone[select].mCol - col);
    if(dRow + dCol != 1)
        return false;

    if(this->mStone[select].mStoneId < 16)
    {
        if(row > this->mStone[select].mRow)
            return false;
        if(this->mStone[select].mRow >= 5)
        {
            if(row == this->mStone[select].mRow )
                return false;
        }
    }
    else
    {
        if(row < this->mStone[select].mRow)
            return false;
        if(this->mStone[select].mRow <= 4)
        {
            if(row == this->mStone[select].mRow )
                return false;
        }
    }
    return true;
}

int Board::getStoneCount(int row1, int col1, int row2, int col2)
{
    int ret=0;
    if(row1!=row2&&col1!=col2)
        return -1;
    if(row1==row2)
    {
        if(col1>col2)
        {
            int temp=col1;
            col1=col2;
            col2=temp;
        }
        for(int i=col1+1;i<col2;++i)
        {
            if(this->getStoneId(row1,i)!=-1)
                ++ret;
        }
    }
    else
    {
        if(row1>row2)
        {
            int temp=row1;
            row1=row2;
            row2=temp;
        }
        for(int i=row1+1;i<row2;++i)
        {
            if(this->getStoneId(i,col1)!=-1)
                ++ret;
        }
    }
    return ret;
}






























