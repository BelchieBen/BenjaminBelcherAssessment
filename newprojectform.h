#ifndef NEWPROJECTFORM_H
#define NEWPROJECTFORM_H

#include <QDialog>
#include <QAction>
#include <QMessageBox>

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

private slots:
    void onCreateProjectBtnClicked();
    void createListMenus();
    void assignUser();
    void removeUser();
};

#endif // NEWPROJECTFORM_H
