#include "choselevelscene.h"
#include <QIcon>
#include <mybutton.h>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
ChoseLevelScene::ChoseLevelScene(QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(650,1000);
    this->setWindowIcon(QIcon());
    this->setWindowTitle("ChoseLevelScene");

    MyButton *backBtn=new MyButton(":/Image/backBtn");
    backBtn->setParent(this);
    backBtn->setFixedSize(150,100);
    backBtn->move(315,this->height()*0.845);

    connect(backBtn,&QPushButton::clicked,[=](){

        backBtn->Zoom1();
        backBtn->Zoom2();

        emit this->choseSceneBack();

        qDebug()<<"切换至开始关卡界面";
    });

    gameWidget = new GameWidget;
    gameWidget->setWindowTitle("Have fun!");

    QDesktopWidget *desktop = QApplication::desktop();
    gameWidget->move(((desktop->width())-gameWidget->width())/2,0);

    MyButton *choseBtn=new MyButton(":/Image/scene1.jpg");
    choseBtn->setParent(this);
    choseBtn->move(this->width()*0.5-145,this->height()*0.21);

    MyButton *choseBtn2=new MyButton(":/Image/scene2.jpg");
    choseBtn2->setParent(this);
    choseBtn2->move(this->width()*0.5-145,this->height()*0.32);

    MyButton *choseBtn3=new MyButton(":/Image/scene3.jpg");
    choseBtn3->setParent(this);
    choseBtn3->move(this->width()*0.5-145,this->height()*0.43);

    connect(choseBtn,&QPushButton::clicked,[=](){

        choseBtn->Zoom1();
        choseBtn->Zoom2();
        QTimer::singleShot(400,this,[=](){
            this->hide();
            gameWidget->setWindowTitle("Easy");
            gameWidget->InitGame(800);
            gameWidget->show();
        });
        qDebug()<<"切换简单难度界面";
    });

    connect(choseBtn2,&QPushButton::clicked,[=](){

        choseBtn2->Zoom1();
        choseBtn2->Zoom2();
        QTimer::singleShot(400,this,[=](){
            this->hide();
            gameWidget->setWindowTitle("Common");
            gameWidget->InitGame(400);
            gameWidget->show();
        });
        qDebug()<<"切换至进阶难度界面";
    });

    connect(choseBtn3,&QPushButton::clicked,[=](){

        choseBtn3->Zoom1();
        choseBtn3->Zoom2();
        QTimer::singleShot(400,this,[=](){
            this->hide();
            gameWidget->setWindowTitle("Hard");
            gameWidget->InitGame(100);
            gameWidget->show();
        });
        qDebug()<<"切换至困难难度界面";
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
