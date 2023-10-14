#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/logo.png"));
    MainWindow w;
    w.setWindowTitle("Аукцион знаний");
    w.show();
    return a.exec();
}
