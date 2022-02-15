#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include "models/user.h"
#include "services/taskdataservice.h"

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

private slots:
    void returnToMainDashboard();
signals:
    void returnToDashboard();
};

#endif // PROFILE_H
