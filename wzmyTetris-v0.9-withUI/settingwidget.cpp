#include "settingwidget.h"
#include <QPainter>
#include "mybutton.h"
#include <QDebug>
#include <QMovie>
#include <QTimer>
#include "StartMainWindow.h"

settingWidget::settingWidget(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Settings");
    this->setFixedSize(400,800);

    //开始按钮
    MyButton * startBtn = new MyButton(":/res/start1.png");
    startBtn->setParent(this);
    startBtn->move(70,150);
    connect(startBtn,&MyButton::clicked,[=]()
    {
       startBtn->Zoom1();
       startBtn->Zoom2();
       QTimer::singleShot(500,this,[=]()
       {
           this->hide();
       });
    });


    //重开按钮
    MyButton * restartBtn = new MyButton(":/res/restart .png");
    restartBtn->setParent(this);
    restartBtn->move(70,300);
    connect(restartBtn,&MyButton::clicked,[=]()
    {
       restartBtn->Zoom1();
       restartBtn->Zoom2();
       QTimer::singleShot(500,this,[=]()
       {
           this->hide();
           //还要添加重开的功能
       });
    });


    //音乐按钮
    MyButton * musicBtn = new MyButton(":/res/music.png");
    musicBtn->setParent(this);
    musicBtn->move(70,450);
    connect(musicBtn,&MyButton::clicked,[=]()
    {
       musicBtn->Zoom1();
       musicBtn->Zoom2();
       //功能还未实现
    });


    //home按钮
    MyButton * homeBtn = new MyButton(":/res/home.png");
    homeBtn->setParent(this);
    homeBtn->move(70,600);
    connect(homeBtn,&MyButton::clicked,[=]()
    {
       homeBtn->Zoom1();
       homeBtn->Zoom2();
       QTimer::singleShot(500,this,[=]()
       {
           this->hide();
           emit this->backToMainWindow();
       });
    });
}

void settingWidget::paintEvent (QPaintEvent *)
{
    //绘制背景图
    QPainter painter(this);
    QPixmap bgpix;
    bgpix.load(":/res/settingbackground.jpg");
    painter.drawPixmap(0,0,bgpix);
}
