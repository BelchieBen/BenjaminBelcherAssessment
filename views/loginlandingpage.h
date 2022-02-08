#ifndef LOGINLANDINGPAGE_H
#define LOGINLANDINGPAGE_H

#include <QDialog>
#include <QPushButton>
#include <QSqlQuery>
#include "services/projectdataservice.h"
#include "views/maindashboard.h"
#include "models/user.h"
#include "globals/userroles.h"
#include "views/forms/newprojectform.h"

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
    user usr;
    UserRoles roles;
    NewProjectForm newproject;

private slots:
    void button_pushed();
    void createprojectBtnClicked();
    void loadProjects();
    void addCreateProjectBtn();
};

#endif // LOGINLANDINGPAGE_H
