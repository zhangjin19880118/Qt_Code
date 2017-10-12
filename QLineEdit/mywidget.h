#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

signals:

public slots:
    void OnClicked();
    void OnReleased();
private:
    QLineEdit *edit1;
    QLineEdit *edit2;
    QLineEdit *edit3;
    QLineEdit *edit4;
    QPushButton *button1;
    QPushButton *button2;
};

#endif // MYWIDGET_H
