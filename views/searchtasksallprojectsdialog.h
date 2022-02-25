#ifndef SEARCHTASKSALLPROJECTSDIALOG_H
#define SEARCHTASKSALLPROJECTSDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "services/taskdataservice.h"
#include "models/task.h"
#include "delegates/tasksearchresultdelegate.h"
#include "views/taskdetails.h"

namespace Ui {
class SearchTasksAllProjectsDialog;
}

class SearchTasksAllProjectsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchTasksAllProjectsDialog(QWidget *parent = nullptr, QList<Task> tasks = {});
    ~SearchTasksAllProjectsDialog();

    const QString &getSearch() const;

private:
    Ui::SearchTasksAllProjectsDialog *ui;
    QList<Task> tasks;
    TaskDataService _taskDataService;

private slots:
    void createTaskWidget();
    void closeDialog();
    void openTask();
};

#endif // SEARCHTASKSALLPROJECTSDIALOG_H
