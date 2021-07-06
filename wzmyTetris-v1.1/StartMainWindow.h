#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "choselevelscene.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *);

    //维护选择场景的指针
    ChoseLevelScene *choseLevelScene;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
