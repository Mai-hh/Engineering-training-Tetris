#include "mybutton.h"

////MyButton::MyButton(QWidget *parent) : QPushButton(parent)
////{

//}

MyButton::MyButton(QString normalImg,QString pressImg){

    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

   QPixmap pix;
   pix.load(this->normalImgPath);


   //设置按键大小
   this->setFixedSize(100,100);

   //设置不规则图片样式
   this->setStyleSheet("QPushButton{border:Opx}");

   //设置图片
   this->setIcon(pix);

   this->setIconSize(QSize(100,100));



}
