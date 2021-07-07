#include "StartMainWindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QPainter>
#include "mybutton.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include "choselevelscene.h"
#include "settingwidget.h"
#include <QSound>
#include <QRadioButton>
#include <QApplication>
#include <QDesktopWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSound *startsound=new QSound(":/res/bgm.wav");
    QSound * bgm2 = new QSound(":/res/bgm2.0.wav");
    startsound->play();
    startsound->setLoops(-1);
    connect(ui->actionclose,&QAction::triggered,[=](){

        this->close();

    });

    this->setFixedSize(650,1000);
    this->setWindowIcon(QIcon());
    this->setWindowTitle("StartMainWindow");

    choseLevelScene=new ChoseLevelScene();
    QDesktopWidget *desktop = QApplication::desktop();
    choseLevelScene->move((desktop->width()-choseLevelScene->width())/2,0);
    connect(choseLevelScene,&ChoseLevelScene::choseSceneBack,[=](){

        QTimer::singleShot(400,choseLevelScene,[=](){

        choseLevelScene->hide();
        this->show();});

    });

    MyButton *startBtn=new MyButton(":/Image/startbutton.jpg");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.31);

    connect(startBtn,&QPushButton::clicked,[=](){

        startBtn->Zoom1();
        startBtn->Zoom2();

        QTimer::singleShot(400,this,[=](){

        this->hide();
        choseLevelScene->show();
        //qDebug()<<"切换至选择关卡界面";

    });

    });

    MyButton *stopBtn=new MyButton(":/Image/settingbutton.jpg");
    stopBtn->setParent(this);
    stopBtn->move(this->width()*0.5-stopBtn->width()*0.5,this->height()*0.5);

    connect(stopBtn,&QPushButton::clicked,[=](){

        stopBtn->Zoom1();
        stopBtn->Zoom2();


        //创建音乐对话框
        QDialog music(this);
        music.setFixedSize(400,200);
        music.setWindowTitle("Music");

        //创建两个单选项
        QRadioButton *radioClose = new QRadioButton("关闭",&music);
        QRadioButton *radioOpen = new QRadioButton("经典音乐",&music);
        QRadioButton *radioOpen2 = new QRadioButton("动感电音",&music);
        radioClose->move(100,30);
        radioOpen->move(100,60);
        radioOpen2->move(100,90);

        //检测两个按钮的状态并设置音乐
        connect(radioClose,&QRadioButton::toggled,[=](bool checked){
        if(checked == true)
        {
               startsound->stop();
               bgm2->stop();
        }
        });
        connect(radioOpen,&QRadioButton::toggled,[=](bool checked){
           if(checked == true)
           {
               startsound->play();
               bgm2->stop();
               startsound->setLoops(-1);//无限循环
           }
        });
        connect(radioOpen2,&QRadioButton::toggled,[=](bool checked){
           if(checked == true)
           {
               bgm2->play();
               bgm2->setLoops(-1);//无限循环
               startsound->stop();
           }
        });
        music.resize(200,100);
        music.exec();

    });

    MyButton *topBtn=new MyButton(":/Image/topbutton.jpg");
    topBtn->setParent(this);
    topBtn->setFixedSize(110,110);
    topBtn->move(44,838);

    connect(topBtn,&QPushButton::clicked,[=](){

        topBtn->Zoom1();
        topBtn->Zoom2();
        qDebug()<<"打开排行榜";
    });


}

void MainWindow::paintEvent(QPaintEvent *){

    //设置背景图
    QPixmap pix;
    pix.load(":/Image/startbeijing1.webp");

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

