#include<QCoreApplication>
#include<QMap>
#include<QDebug>

int main(int argc,char *argv[])
{
    QCoreApplication app(argc,argv);

    QMap<QString,int> m;
    m.insert("aaa",11);
    m.insert("bbb",22);
    m.insert("ccc",33);

    for(auto it=m.begin();it!=m.end();++it)
        qDebug()<<it.key()<<it.value();

    return app.exec();
}
