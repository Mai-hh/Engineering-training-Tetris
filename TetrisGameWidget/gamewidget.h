#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H
#include "gameoverwidget.h"
#include <QWidget>
#include <QPushButton>
#include <QDialog>

const int Margin = 10;
const int Row = 16;
const int Line = 36;
const int SideLength = 25;

QT_BEGIN_NAMESPACE
namespace Ui { class GameWidget; }
QT_END_NAMESPACE

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

    QPushButton *btn_pause;
    QDialog *gameOver_dlg;
    GameOverWidget *gameOverWidget;
    void paintEvent(QPaintEvent *event);
    void btn_set();
    void GameOver();

private:
    Ui::GameWidget *ui;
};
#endif // GAMEWIDGET_H
