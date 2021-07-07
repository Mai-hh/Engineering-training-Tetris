#ifndef CHOSELEVELSCENE_H
#define CHOSELEVELSCENE_H

#include <QWidget>
#include "gamewidget.h"
class ChoseLevelScene : public QWidget
{
    Q_OBJECT
public:
    explicit ChoseLevelScene(QWidget *parent = nullptr);
    GameWidget *gameWidget;
    void paintEvent(QPaintEvent *);


signals:
    void choseSceneBack();

public slots:
};

#endif // CHOSELEVELSCENE_H
