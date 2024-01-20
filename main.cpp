#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString::fromUtf8("Bankomat"));
    w.setMinimumSize(1500,1100);
    w.setMaximumSize(1500,1100);
    w.show();
    return a.exec();
}
