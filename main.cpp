#include "mainwindow.h"
#include "user.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    dataservice _data;
    user usr;

    _data.connectToDb();

    MainWindow w;
    w.show();
    int ret = a.exec();
    usr.removeCurrentUsr();;
    return ret;
}
