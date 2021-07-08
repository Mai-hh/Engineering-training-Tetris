#include "StartMainWindow.h"

#include <QApplication>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QDesktopWidget *desktop = QApplication::desktop();
    w.move((desktop->width()-w.width())/2,0);
    w.show();
    return a.exec();
}
