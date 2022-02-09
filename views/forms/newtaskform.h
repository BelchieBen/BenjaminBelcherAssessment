#ifndef NEWTASKFORM_H
#define NEWTASKFORM_H

#include <QDialog>
#include <QSqlQuery>
#include <QString>
#include <ctime>
#include <QMessageBox>
#include <QSqlError>
#include "globals/taskstates.h"
#include "services/taskdataservice.h"
#include "models/user.h"

namespace Ui {
class NewTaskForm;
}

class NewTaskForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewTaskForm(QWidget *parent = nullptr);
    ~NewTaskForm();

private:
    Ui::NewTaskForm *ui;
    TaskStates taskStates;
    TaskDataService _taskDataService;
    user usr;

private slots:
    void onCreateTaskBtnPressed();
    void populateProjectBox();

signals:
    void addedItem();
};

#endif // NEWTASKFORM_H
