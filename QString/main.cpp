#include<QCoreApplication>
#include<QString>
#include<QByteArray>
#include<QDebug>
#include<QList>

int main(int argc,char **argv)
{
    QCoreApplication app(argc,argv);

    QString str = "薛老师";
    str += "是一个坏蛋!";
    QList<QString> subStrs = str.split("一");
    for(auto it=subStrs.begin();it!=subStrs.end();++it)
    {
        qDebug()<<*it;
    }

    return app.exec();
}
