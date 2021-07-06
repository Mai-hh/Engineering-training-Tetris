#include "gamewidget.h"
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <mybutton.h>
#include <QLabel>
#include <QFont>
GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(650,1000);
    btn_set();
    btn_pause->setParent(this);
    GameOver();

    this->line=0;

    QLabel *label=new QLabel;
    label->setParent(this);
    QString str=QString("Points: %1").arg(this->line*10);
    QFont font;
    font.setFamily("Segeo UI");
    font.setPointSize(20);

    label->setFont(font);
    label->setText(str);
    label->setGeometry(QRect(Margin, Margin+SideLength*Line, 300, 100));//设置位置和大小


    //创建暂停界面
    stWidget = new settingWidget(this);

    connect(btn_pause,&QPushButton::clicked,[=](){
        //动画是否要做?
        //直接呼出暂停界面，无需隐藏游戏界面
        stWidget->exec();
    });

    connect(stWidget,&settingWidget::backToMainWindow,[=](){
        this->hide();
       emit this->backToMainWindow();
    });

}

void GameWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPen pen;

    painter.setPen(pen);


    QBrush brush(QColor(242,107,92));

    painter.setBrush(brush);

    painter.drawRect(QRect(0,0,this->width(),this->height()));


    painter.drawRect(Margin, Margin, SideLength*Row, SideLength*Line);

    QPixmap pix;
    pix.load(":/Image/piece.jpg");

    painter.drawPixmap(Margin, Margin, SideLength*Row, SideLength*Line,pix);

    pix.load(":/Image/piece1.jpg");

    painter.drawPixmap(Margin+SideLength*Row+10, Margin, 220, 280,pix);

    pix.load(":/Image/piece3.jpg");

    painter.drawPixmap(Margin+SideLength*Row+10, Margin+300, 220, 500,pix);






}

void GameWidget::btn_set()
{
    btn_pause = new MyButton(":/Image/stop.png");
    btn_pause->setFixedSize(100,100);
    btn_pause->move(this->width()*0.75,this->height()*0.85);
//    btn_pause->setText("Pause");
//SideLength * (Row+2) + Margin, Margin + SideLength * (Line-2)
}

void GameWidget::GameOver()
{

    QPushButton *btn_gameOver = new QPushButton(this);

    btn_gameOver->setFixedSize(50,50);
    btn_gameOver->move(SideLength * (Row+2) + Margin, Margin);
    btn_gameOver->setText("GG");

    gameOverWidget = new GameOverWidget(this);
    connect(btn_gameOver,&QPushButton::clicked,[=](){
        gameOverWidget->exec();
    });

}


