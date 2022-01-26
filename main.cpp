#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    dataservice _data;

    _data.connectToDb();

    MainWindow w;
    w.show();
    return a.exec();
}
