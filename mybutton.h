#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyButton(QWidget *parent = nullptr);

    MyButton(QString normalImg,QString pressImg="");

    QString normalImgPath;
    QString pressImgPath;



signals:

public slots:
};

#endif // MYBUTTON_H
