#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include "models/user.h"
#include "services/taskdataservice.h"
#include "taskdetails.h"
#include "views/forms/loginform.h"

namespace Ui {
class Profile;
}

class Profile : public QWidget
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);  
    void populateTreeWidget(user u);
    ~Profile();

private:
    Ui::Profile *ui;
    user usr;
    TaskDataService _taskDataService;
    LoginForm login;

private slots:
    void returnToMainDashboard();
    void openTaskDetailsFromProfile(Task *t);
    void sendSignal();
    void logoutUser();
signals:
    void returnToDashboard();
    void SeeMoreClicked(Task);
};

#endif // PROFILE_H
