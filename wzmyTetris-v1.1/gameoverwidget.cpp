#include "gameoverwidget.h"

GameOverWidget::GameOverWidget(QWidget *parent) : QDialog(parent)
{
    restart = new QPushButton(this);
    backToStart = new QPushButton(this);

    restart->setText("Restart");
    backToStart->setText("Back");
    restart->setFixedSize(100,25);
    restart->move(75,150);
    backToStart->setFixedSize(100,25);
    backToStart->move(75,300);
    this->setFixedSize(250,450);
    this->setWindowTitle("Game over !");
}
