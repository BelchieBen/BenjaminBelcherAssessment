#ifndef LOGINLANDINGPAGE_H
#define LOGINLANDINGPAGE_H

#include <QDialog>
#include <QPushButton>
#include <QSqlQuery>
#include "projectdataservice.h"
#include "maindashboard.h"

namespace Ui {
class LoginLandingPage;
}

class LoginLandingPage : public QDialog
{
    Q_OBJECT

public:
    explicit LoginLandingPage(QWidget *parent = nullptr);
    ~LoginLandingPage();

private:
    Ui::LoginLandingPage *ui;

private slots:
    void button_pushed();
};

#endif // LOGINLANDINGPAGE_H
