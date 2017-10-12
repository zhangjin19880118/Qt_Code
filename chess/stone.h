#ifndef STONE_H
#define STONE_H

#include "util.h"
#include <QPainter>

class Stone
{
public:
    Stone();
    enum Type{Shuai,Shi,Xiang,Che,Ma,Pao,Bing};
    int mRow;
    int mCol;
    Type type;
    bool mDeath;
    int mStoneId;
    int &d;
    void drawStone(QPainter &p,int selectId);
};

#endif // STONE_H
