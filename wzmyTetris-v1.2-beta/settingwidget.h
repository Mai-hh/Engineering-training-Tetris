#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QDialog>

class settingWidget : public QDialog
{
    Q_OBJECT
public:
    explicit settingWidget(QWidget *parent = nullptr);

    void paintEvent (QPaintEvent *);

signals:
    void backToMainWindow();
    void ClockRun();
    void Restart();
public slots:
};

#endif // SETTINGWIDGET_H
