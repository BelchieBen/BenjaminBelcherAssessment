#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "views/forms/registerform.h"
#include "views/forms/loginform.h"
#include "views/quickloginpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QuickLoginPage quickLoginPage;

private slots:
    void onLoginPressed();
    void onRegisterPressed();
};
#endif // MAINWINDOW_H
