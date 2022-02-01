#include "newtaskform.h"
#include "ui_newtaskform.h"
#include "taskdataservice.h"

NewTaskForm::NewTaskForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTaskForm)
{
    ui->setupUi(this);
    QStringList effortPoints = (QStringList()<<"1"<<"2"<<"3"<<"5"<<"8"<<"10");
    QStringList priority = (QStringList()<<"Minor"<<"Medium"<<"Major");
    ui->EffortBox->addItems(effortPoints);
    ui->PriorityBox->addItems(priority);
    connect(ui->CreateTaskBtn, SIGNAL(released()), this, SLOT(onCreateTaskBtnPressed()));
}

void NewTaskForm::onCreateTaskBtnPressed(){
    QString title = ui->Title->text();
    QString desc =  ui->Description->toPlainText();
    QString effort = ui->EffortBox->currentText();
    QString priority = ui->PriorityBox->currentText();
    QString project = "test project";

    TaskDataService _taskDataService;
    bool result;
    result = _taskDataService.createTask(title, desc, effort, priority, project);

    QMessageBox messageBox;

    if(result){
        qDebug() << "Added Task!";
        messageBox.setText("Added Task!");
        messageBox.exec();
        emit addedItem();
        this->hide();
    }
    else{
        messageBox.critical(0,"Error","There was an error when creating the task, please try again!");
    }
}

NewTaskForm::~NewTaskForm()
{
    delete ui;
}


