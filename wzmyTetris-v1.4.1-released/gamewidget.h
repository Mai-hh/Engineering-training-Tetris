#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "settingwidget.h"
#include <QKeyEvent>

const int Margin = 10;
const int Row = 16;
const int Line = 36;
const int SideLength = 25;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE
};
struct Border
{
    int ubound;
    int dbound;
    int lbound;
    int rbound;
};//记录边界
struct block_point
{
    int pos_x;
    int pos_y;
};//记录方块抽象坐标
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    void InitGame(int speed);//初始化游戏，参数决定游戏速度
    void GameOver();//游戏结束
    void StartGame();//游戏开始
    void CreateBlock(int block[4][4],int blockId);
    void ResetBlock();
    void GetBorder(int block[4][4],Border &border);
    void BlockRotate(int block[4][4]);
    void BlockMove(Direction dir);
    bool IsCollide(int x,int y,Direction dir);
    void ConvertStable(int x,int y);
    void btn_set();
    int speed_ms,refresh_ms;
public:
    explicit GameWidget(QWidget *parent = nullptr);
    QPushButton *btn_pause;
    QDialog *gameOver_dlg;
    settingWidget *stWidget;
    virtual void paintEvent(QPaintEvent *) ;

    virtual void timerEvent(QTimerEvent *) ;

    virtual void keyPressEvent(QKeyEvent *);




private:
    int GameArea[Line][Row];
    block_point blockPos;
    int curBlock[4][4];
    Border curBorder;
    int nextBlock[4][4];
    int score;
    int gameTimer,paintTimer;
signals:
    void backToMainWindow();

public slots:
};

#endif // GAMEWIDGET_H
