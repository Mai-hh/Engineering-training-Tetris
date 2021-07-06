#include "settingwidget.h"
#include <QPainter>
#include "mybutton.h"
#include <QDebug>
#include <QMovie>
#include <QTimer>
#include "StartMainWindow.h"
#include <QSound>
#include <QPushButton>
#include <QRadioButton>
#include <QDialog>

settingWidget::settingWidget(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Settings");
    this->setFixedSize(300,400);

    QSound *startsound=new QSound(":/res/bgm.wav");
    //开始按钮
    MyButton * startBtn = new MyButton(":/Image/settingbutton2");
    startBtn->setParent(this);
    startBtn->setFixedSize(200,90);
    startBtn->move(this->width()*0.2,this->height()*0.18);
    connect(startBtn,&MyButton::clicked,[=]()
    {
       startBtn->Zoom1();
       startBtn->Zoom2();
       QTimer::singleShot(400,this,[=]()
       {
           emit this->ClockRun();
           this->hide();
       });
    });


    //重开按钮
    MyButton * restartBtn = new MyButton(":/Image/settingbutton3");
    restartBtn->setParent(this);
    restartBtn->setFixedSize(200,90);
    restartBtn->move(this->width()*0.2,this->height()*0.36);
    connect(restartBtn,&MyButton::clicked,[=]()
    {
       restartBtn->Zoom1();
       restartBtn->Zoom2();
       QTimer::singleShot(400,this,[=]()
       {
           emit this->Restart();
           this->hide();
       });
    });


    //音乐按钮
//    MyButton * musicBtn = new MyButton(":/Image/settingbutton4");
//    musicBtn->setParent(this);
//    musicBtn->setFixedSize(200,90);
//    musicBtn->move(this->width()*0.2,this->height()*0.54);
//    connect(musicBtn,&MyButton::clicked,[=]()
//    {
//       musicBtn->Zoom1();
//       musicBtn->Zoom2();
       //功能还未实现
       //暂停时先停bgm
//       startsound->stop();
       //创建音乐对话框
//       QDialog music(this);
//       music.setFixedSize(400,200);

       //创建两个单选项
//       QRadioButton *radioClose = new QRadioButton("关闭",&music);
//       QRadioButton *radioOpen = new QRadioButton("经典音乐",&music);
//       radioClose->setChecked(true);//默认关闭bgm
//       radioClose->move(100,30);
//       radioOpen->move(100,60);

       //检测两个按钮的状态并设置音乐
//       connect(radioClose,&QRadioButton::toggled,[=](bool checked){
//           if(checked == true)
//                  startsound->stop();
//           });
//           connect(radioOpen,&QRadioButton::toggled,[=](bool checked){
//              if(checked == true)
//                  startsound->play();
//                  startsound->setLoops(-1);//无限循环
//           });
//       music.resize(200,100);
//       music.exec();
//    });


    //home按钮
    MyButton * homeBtn = new MyButton(":/Image/settingbutton5");
    homeBtn->setParent(this);
    homeBtn->setFixedSize(200,90);
    homeBtn->move(this->width()*0.2,this->height()*0.54);
    connect(homeBtn,&MyButton::clicked,[=]()
    {
       homeBtn->Zoom1();
       homeBtn->Zoom2();
       QTimer::singleShot(200,this,[=]()
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

    QPen pen;

    painter.setPen(pen);


    QBrush brush(QColor(90,90,90));

    painter.setBrush(brush);

    painter.drawRect(QRect(0,0,this->width(),this->height()));
}
