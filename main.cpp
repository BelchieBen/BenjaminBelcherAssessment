#include "mainwindow.h"
#include "models/user.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QWindow::setIcon();
    QFont font("Gilroy");
    font.setWeight(QFont::Medium);
    a.setFont(font);

    // Assigning resources

    dataservice _data;
    user usr;

    _data.connectToDb();

    MainWindow w;
    w.show();
    int ret = a.exec();

    // Freeing resouces & shutdown tasks
    if(!usr.isRememberMeTrue()){
        usr.removeCurrentUsr();
    }
    else{

    }
    return ret;
}
