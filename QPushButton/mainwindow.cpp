#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    WinExec("calc",SW_NORMAL);
}

void MainWindow::on_pushButton_2_clicked()
{
    WinExec("mspaint",SW_NORMAL);
}
