#include "widget.h"
#include "ui_widget.h"

#include "dict.h"
#include <QDebug>
#define cout qDebug() //没有分号

//全局变量的结构体指针
struct dict *p;
int n;  //单词个数

//构造函数做初始化
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    p = NULL;
    n = 0;

    //加载文件内容
    n = open_dict(&p, "./dict_utf_8.txt");
    if(n == 0)
    {
        cout << "open_dict err";
        return;
    }

}

//析构函数，清理
Widget::~Widget()
{
    if(p != NULL)
    {
        free_dict(p, n);
    }

    delete ui;
}

//按钮处理函数
void Widget::on_pushButton_clicked()
{
    //1、获取编辑区的内容， QString
    QString str = ui->lineEdit->text();

    //2、不为空才执行
    if(str == "")
    {
        ui->label->setText("输入内容不能为空！！！");
        return;
    }

    //3、QString --> char *
    const char *key = str.toStdString().data();

    //4、char content[2048], 查询
    char content[2048] = {0};
    int ret;

    // 如果有内容，显示，没有内容，显示没有内容
    ret = search_dict(p, n, key, content);
    if(ret == 0) //没有
    {
         ui->label->setText("没有此词汇！！！");
    }
    else
    {
        ui->label->setText(   content     );
    }


}
