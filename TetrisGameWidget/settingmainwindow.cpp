#include "settingmainwindow.h"
#include <QPainter>
#include "settingpushbtn.h"
#include <QDebug>
#include <QMovie>
#include "gamewidget.h"

SettingMainWindow::SettingMainWindow()
{
    setWindowTitle("暂停");
    this->setFixedSize(400,800);

    //开始按钮
    SettingPushBtn * startBtn = new SettingPushBtn(":/setting/pic/start1.png");
    startBtn->setParent(this);
    startBtn->move(145,200);

    connect(startBtn,&SettingPushBtn::clicked,[=](){
        //做一个弹起的特效
        startBtn->zoom1();
    });

}

void SettingMainWindow::paintEvent (QPaintEvent *)
{
    //绘制背景图
    QPainter painter(this);
    QPixmap bgpix;
    bgpix.load(":/setting/pic/settingbackground.jpg");
    painter.drawPixmap(0,0,bgpix);
}


