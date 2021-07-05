#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "gameoverwidget.h"
#include "settingwidget.h"

const int Margin = 10;
const int Row = 16;
const int Line = 36;
const int SideLength = 25;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    QPushButton *btn_pause;
    QDialog *gameOver_dlg;
    GameOverWidget *gameOverWidget;
    settingWidget *stWidget;
    void paintEvent(QPaintEvent *event);
    void btn_set();
    void GameOver();

signals:
    void backToMainWindow();

public slots:
};

#endif // GAMEWIDGET_H
