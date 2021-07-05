#include "choselevelscene.h"
#include <QIcon>
#include <mybutton.h>
#include <QTimer>
#include <QDebug>
ChoseLevelScene::ChoseLevelScene(QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(650,1000);
    this->setWindowIcon(QIcon());
    this->setWindowTitle("ChoseLevelScene");

    MyButton *backBtn=new MyButton(":/stop.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&QPushButton::clicked,[=](){

        backBtn->Zoom1();
        backBtn->Zoom2();

        emit this->choseSceneBack();

        qDebug()<<"切换至开始关卡界面";
    });

    MyButton *choseBtn=new MyButton(":/stop.png");
    gameWidget = new GameWidget;
    gameWidget->setWindowTitle("Have fun!");

    choseBtn->setParent(this);
    choseBtn->move(this->width()-backBtn->width(),this->height()*0.5);

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
