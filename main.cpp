#include "mainwindow.h"
#include "user.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Assigning resources

    dataservice _data;
    user usr;

    _data.connectToDb();

    MainWindow w;
    w.show();
    int ret = a.exec();

    // Freeing resouces & shutdown tasks

    usr.removeCurrentUsr();;
    return ret;
}
