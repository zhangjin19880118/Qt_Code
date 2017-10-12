#include "mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("中国象棋");
    this->resize(800,1024);

    this->pBoard=new Board;
    this->setCentralWidget(this->pBoard);
}
