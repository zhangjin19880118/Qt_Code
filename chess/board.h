#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include "util.h"
#include "stone.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void drawPlate(QPainter &p);
    void drawFlower(QPainter &p,int row,int col);
    void mousePressEvent(QMouseEvent *event);
    int getStoneId(int row,int col);
    void selectStone(int select);
    void moveStone(int select,int kill,int row,int col);
    bool canMovesStone(int select,int kill,int row,int col);
    bool canMoveShuai(int select,int kill,int row,int col);
    bool canMoveShi(int select,int kill,int row,int col);
    bool canMoveXiang(int select,int kill,int row,int col);
    bool canMoveChe(int select,int kill,int row,int col);
    bool canMoveMa(int select,int kill,int row,int col);
    bool canMovePao(int select,int kill,int row,int col);
    bool canMoveBing(int select,int kill,int row,int col);
    int getStoneCount(int row1, int col1, int row2, int col2);
public:
    int &d;
    Stone mStone[32];
    int selectId;
    bool redTurn;
signals:

public slots:
};

#endif // BOARD_H
