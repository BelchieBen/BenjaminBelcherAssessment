#ifndef SEARCHTASKSALLPROJECTSDIALOG_H
#define SEARCHTASKSALLPROJECTSDIALOG_H

#include <QDialog>
#include "services/taskdataservice.h"
#include "models/task.h"
#include "delegates/tasksearchresultdelegate.h"

namespace Ui {
class SearchTasksAllProjectsDialog;
}

class SearchTasksAllProjectsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchTasksAllProjectsDialog(QWidget *parent = nullptr, QString search = "");
    ~SearchTasksAllProjectsDialog();

    const QString &getSearch() const;

private:
    Ui::SearchTasksAllProjectsDialog *ui;
    QString search;
    TaskDataService _taskDataService;

private slots:
    void getSearchResults(QString term);
};

#endif // SEARCHTASKSALLPROJECTSDIALOG_H
