#include "gamewidget.h"
#include <QPushButton>
#include <QPainter>
GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(650,1000);
    btn_set();
    GameOver();
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QBrush brush(QColor(255,255,255));

    painter.setBrush(brush);

    painter.drawRect(Margin, Margin, SideLength*Row, SideLength*Line);
}

void GameWidget::btn_set()
{
    btn_pause = new QPushButton(this);
    btn_pause->setFixedSize(50,50);
    btn_pause->move(SideLength * (Row+2) + Margin, Margin + SideLength * (Line-2));
    btn_pause->setText("Pause");
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


