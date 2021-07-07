#include "mybutton.h"
#include <QPropertyAnimation>
#include <QTimer>
#include <QDebug>
#include <QCursor>

////MyButton::MyButton(QWidget *parent) : QPushButton(parent)
////{

//}

MyButton::MyButton(QString normalImg,QString pressImg){

    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

   QPixmap pix;
   pix.load(this->normalImgPath);

   //设置按键大小
   this->setFixedSize(290,100);

   //设置不规则图片样式
   this->setStyleSheet("QPushButton{border:Opx}");

   //设置图片
   this->setIcon(pix);
   this->setIconSize(QSize(290,100));
   this->setCursor(QCursor(Qt::PointingHandCursor));


}
void MyButton::Zoom1(){

    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

}

void MyButton::Zoom2(){

    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

}


