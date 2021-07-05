#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H

#include <QDialog>
#include <QPushButton>
class GameOverWidget : public QDialog
{
    Q_OBJECT
public:
    explicit GameOverWidget(QWidget *parent = nullptr);
    QPushButton *restart;
    QPushButton *backToStart;
//    void btn_set();

signals:

public slots:
};

#endif // GAMEOVERWIDGET_H
