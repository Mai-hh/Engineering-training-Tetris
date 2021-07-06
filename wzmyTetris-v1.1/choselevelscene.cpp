#include "choselevelscene.h"
#include <QIcon>
#include <mybutton.h>
#include <QTimer>
#include <QDebug>
#include <QPainter>
ChoseLevelScene::ChoseLevelScene(QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(650,1000);
    this->setWindowIcon(QIcon());
    this->setWindowTitle("ChoseLevelScene");

    MyButton *backBtn=new MyButton(":/Image/backBtn");
    backBtn->setParent(this);
    backBtn->move(this->width()*0.375,this->height()*0.845);

    connect(backBtn,&QPushButton::clicked,[=](){

        backBtn->Zoom1();
        backBtn->Zoom2();

        emit this->choseSceneBack();

        qDebug()<<"切换至开始关卡界面";
    });
    MyButton *choseBtn=new MyButton(":/Image/scene1.jpg");
    gameWidget = new GameWidget;
    gameWidget->setWindowTitle("Have fun!");

    choseBtn->setParent(this);
    choseBtn->move(this->width()*0.5-backBtn->width()*0.5,this->height()*0.32);

    connect(choseBtn,&QPushButton::clicked,[=](){

        choseBtn->Zoom1();
        choseBtn->Zoom2();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            gameWidget->show();
        });
        qDebug()<<"切换至游戏关卡界面";
    });


    connect(gameWidget,&GameWidget::backToMainWindow,[=](){
        emit this->choseSceneBack();
    });


}
void ChoseLevelScene::paintEvent(QPaintEvent *){

    //设置背景图
    QPixmap pix;
    pix.load(":/Image/startbeijing1.webp");

    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

//    //设置标题图
//    pix.load("");
//    painter.drawPixmap(x,y,pix);
}
