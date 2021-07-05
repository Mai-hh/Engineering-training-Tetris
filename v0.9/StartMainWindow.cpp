#include "StartMainWindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QPainter>
#include "mybutton.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include "choselevelscene.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionclose,&QAction::triggered,[=](){

        this->close();

    });

    this->setFixedSize(650,1000);
    this->setWindowIcon(QIcon());
    this->setWindowTitle("StartMainWindow");

    choseLevelScene=new ChoseLevelScene();

    connect(choseLevelScene,&ChoseLevelScene::choseSceneBack,[=](){

        QTimer::singleShot(400,choseLevelScene,[=](){

        choseLevelScene->hide();
        this->show();});

    });

    MyButton *startBtn=new MyButton(":1.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.3);

    connect(startBtn,&QPushButton::clicked,[=](){

        startBtn->Zoom1();
        startBtn->Zoom2();

        QTimer::singleShot(400,this,[=](){

        this->hide();
        choseLevelScene->show();
        qDebug()<<"切换至选择关卡界面";

    });

    });

    MyButton *stopBtn=new MyButton(":stop.png");
    stopBtn->setParent(this);
    stopBtn->move(this->width()*0.5-stopBtn->width()*0.5,this->height()*0.5);

    connect(stopBtn,&QPushButton::clicked,[=](){

        stopBtn->Zoom1();
        stopBtn->Zoom2();
        qDebug()<<"切换至暂停界面";
    });

}

void MainWindow::paintEvent(QPaintEvent *){

    //设置背景图
    QPixmap pix;
    pix.load(":/beijing.jpg");

    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

//    //设置标题图
//    pix.load("");
//    painter.drawPixmap(x,y,pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

