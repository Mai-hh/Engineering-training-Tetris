#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QPainter>
#include <QPushButton>
GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    btn_set();
    GameOver();
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

void GameWidget::btn_set()
{
    btn_pause = new QPushButton(this);
    btn_pause->setFixedSize(50,50);
    btn_pause->move(SideLength * (Row+2) + Margin, Margin + SideLength * (Line-2));
    btn_pause->setText("Pause");
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QBrush brush(QColor(255,255,255));

    painter.setBrush(brush);

    painter.drawRect(Margin, Margin, SideLength*Row, SideLength*Line);
}

GameWidget::~GameWidget()
{
    delete ui;
}

