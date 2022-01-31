#ifndef NEWTASKFORM_H
#define NEWTASKFORM_H

#include <QDialog>
#include <QSqlQuery>
#include <QString>
#include <ctime>
#include <QMessageBox>
#include <QSqlError>

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

private slots:
    void onCreateTaskBtnPressed();

signals:
    void addedItem();
};

#endif // NEWTASKFORM_H
