#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QFileDialog>
#define cout qDebug()

enum mycode
{
    utf_8,gbk
};

enum mycode flag;

QString path;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag=utf_8;
    path="";
}

MainWindow::~MainWindow()
{
    delete ui;
}

//选择utf-8编码显示
void MainWindow::on_actionUtf_8_triggered()
{
    cout << "utf-8";
    ui->label->setText("当前以utf-8编码显示");
    flag=utf_8;
    readFile();
}

//选择gbk编码显示
void MainWindow::on_actionGbk_triggered()
{
    cout << "gbk";
    ui->label->setText("当前以gbk编码显示");
    flag=gbk;
    readFile();
}


void MainWindow::on_actionOpen_triggered()
{
    //1、选择打开文件的路径，Qt，返回文件的路径QString

      path = QFileDialog::getOpenFileName(); //需要头文件#include <QFileDialog>

      readFile();
}

void MainWindow::readFile()
{
    //判断打开路径是否为空
    //if( path.isEmpty() == true)
    if( path == "")
    {
        cout << "文件路径为NULL";
        return;
    }

    cout << "path = " << path.toStdString().data(); //将QString -> char *

    //2、QString -> char *
    //从Qt得到的字符串都是utf-8编码，如果是在windows，需要gbk，会打开失败
    //const char *file = path.toStdString().data();

    //toLocal8Bit(), 转换为本地字符集，如果windows则为gbk编码，如果linux则为utf-8编码
    char *file = path.toLocal8Bit().data();

    //3、打开文件， fopen
    //ANSI C(标准C)使用中文字符串和系统有关，如果是在windows，需要gbk
    //                                  如果是liunx，需要utf-8
    FILE *fp = NULL;
    fp = fopen(file, "rb");
    if(fp == NULL)
    {
        cout << "fopen err";
        return;
    }

    cout << "文件打开成功";

    //4、读取文件内容，fread(), char buf[4*1024]
    char buf[4*1024] = {0};
    int ret;
    QString str;

    while(1)
    {
        memset(buf, 0, sizeof(buf)); //很重要
        //从文件读取内容，放在buf中
        ret = fread(buf, 1, sizeof(buf),  fp);
        //cout << "ret = " << ret;
        if(ret == 0) //文件没有内容
        {
            break; //跳出循环
        }
        //如果读取内容为utf-8
        if(utf_8 == flag)
        {
             str += buf; //str = str + buf; //char * ---> QString
        }
        //如果读取内容为gbk, 把gbk -----> utf-8
        //	//fromLocal8Bit(), 本地字符集转换为utf-8
        //QString tmp = QString::fromLocal8Bit( (const char *)buf);
        else
        {
             str += QString::fromLocal8Bit( (const char *)buf);
        }

    }

    //5、buf内容显示到编辑区， 设置内容，需要参数类型QString
    //Qt控件显示中文，必须是utf-8编码
    ui->textEdit->setText(str);


    //6、关闭文件 fclose()
    fclose(fp);
}

void MainWindow::on_actionSaveas_triggered()
{
    //1、选择保存的路径， Qt， 路径是QString, utf-8
    path = QFileDialog::getSaveFileName();

    writeFile();
}

void MainWindow::writeFile()
{
    if( path.isEmpty() )
    {
        cout << "文件路径为空";
        return;
    }

    cout << "path = " << path.toStdString().data();

    //2、utf-8  转换为本地编码，  QString --> char *
     //从Qt得到的字符串都是utf-8编码，如果是在windows，需要gbk，会打开失败
    //const char *file = path.toStdString().data();

    //toLocal8Bit(), 转换为本地字符集，如果windows则为gbk编码，如果linux则为utf-8编码
    char *file = path.toLocal8Bit().data();

    //3、fopen("wb")
    FILE *fp = NULL;
    fp = fopen(file, "wb");
    if(fp == NULL)
    {
        cout << "fopen err";
        return;
    }

    //4、读取编辑区内容QString，写入文件char *
    // QString ---> char *
    QString str;
    str = ui->textEdit->toPlainText();

    const char *buf = str.toStdString().data(); //QString ---> char *
    size_t size = str.toStdString().size(); //获取字符串的大小

    fwrite(buf, 1, size, fp);

    //5、关闭文件
    fclose(fp);
    fp = NULL;
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCompile_triggered()
{
    /*
      //编译
      int flag = system("gcc C:\\Users\\MikeJiang\\Desktop\\mike.c -o C:\\Users\\MikeJiang\\Desktop\\mike");
      cout << "flag = " << flag;

      if(flag != 0) //代码有问题
      {
          system("cmd /k gcc C:\\Users\\MikeJiang\\Desktop\\mike.c -o C:\\Users\\MikeJiang\\Desktop\\mike");

          return;
      }

      //运行
      system("cmd /k C:\\Users\\MikeJiang\\Desktop\\mike");

      */
      if(path == "")
      {
          cout << "路径为空";
          return;
      }

      //可执行程序的名字
      QString target = path;

      cout << "target1 = " << target;
      target.replace(".c", ""); //把.c替换我空字符
      cout << "target2 = " << target;

      //gcc xxx.c -o xxx
      QString cmd;
      //cmd = QString("gcc %1 -o %2").arg(path).arg(target);
      cmd = "gcc " + path + " -o " + target;
      cout << "cmd = " << cmd;

      int flag;
      //cmd为QString类型
      //转换为本地编码，QString --> char *
      flag = system(  cmd.toLocal8Bit().data()   );
      if(flag != 0)
      {
          cout << "编译的代码有错误";
          cmd = "cmd /k " + cmd;
          cout << cmd;

          system(  cmd.toLocal8Bit().data()   );

          return;
      }

      //运行代码
      cmd = "cmd /k " + target;
      cout << cmd;
      system(  cmd.toLocal8Bit().data()   );
}

void MainWindow::on_actionExit_triggered()
{
    exit(1);
}

void MainWindow::on_actionSave_triggered()
{   
    if(path.isEmpty())
    //if(path="")
    {
        path = QFileDialog::getSaveFileName();

        writeFile();
        return;
    }
    writeFile();
}


void MainWindow::on_actionNew_triggered()
{
  //  ui->textEdit->setText("");
    ui->textEdit->clear();
}
