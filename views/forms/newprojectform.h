#ifndef NEWPROJECTFORM_H
#define NEWPROJECTFORM_H

#include <QDialog>
#include <QAction>
#include <QMessageBox>
#include "services/projectdataservice.h"
#include "models/user.h"

namespace Ui {
class NewProjectForm;
}

class NewProjectForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectForm(QWidget *parent = nullptr);
    ~NewProjectForm();

private:
    Ui::NewProjectForm *ui;
    ProjectDataService _dataService;
    user usr;

private slots:
    void onCreateProjectBtnClicked();
    void createListMenus();
    void assignUser();
    void removeUser();
    void populateAvailableUsrsList();
    void on_SrcUsers_textEdited(const QString &arg1);

signals:
    void projectCreated();
};

#endif // NEWPROJECTFORM_H
