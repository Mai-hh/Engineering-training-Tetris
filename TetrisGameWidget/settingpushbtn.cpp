#include "settingpushbtn.h"
#include <QDebug>
#include <QPropertyAnimation>

//SettingPushBtn::SettingPushBtn(QWidget *parent) : QPushButton(parent)
//{

//}
SettingPushBtn::SettingPushBtn (QString normalImg,QString pressImg)
{
    this->normalImgPath = normalImg;
    this->presssImgPath = pressImg;

    QPixmap startPix;
    bool ret = startPix.load(normalImg);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }

    //设置图片固定大小
    this->setFixedSize(startPix.width(),startPix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(startPix);

    //设置图标大小
    this->setIconSize(QSize(startPix.width(),startPix.height()));
}


void SettingPushBtn::zoom1()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //动画开始
    animation->start();
}

void SettingPushBtn::zomm2()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //动画开始
    animation->start();


}
