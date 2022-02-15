#include "views/forms/newtaskform.h"
#include "ui_newtaskform.h"


NewTaskForm::NewTaskForm(QWidget *parent, int projectId) :
    QDialog(parent),
    ui(new Ui::NewTaskForm)
{
    ui->setupUi(this);
    this->projId = projectId;

    QStringList effortPoints = (QStringList()<<"1"<<"2"<<"3"<<"5"<<"8"<<"10");
    QStringList priority = (QStringList()<<"Minor"<<"Medium"<<"Major");
    ui->AssigneeBox->addItems(_taskDataService.populatingAssigneesList(projId));
    ui->EffortBox->addItems(effortPoints);
    ui->PriorityBox->addItems(priority);
    connect(ui->CreateTaskBtn, SIGNAL(released()), this, SLOT(onCreateTaskBtnPressed()));

    //populateProjectBox();
}

void NewTaskForm::onCreateTaskBtnPressed(){
    QString title = ui->Title->text();
    QString desc =  ui->Description->toPlainText();
    QString effort = ui->EffortBox->currentText();
    QString priority = ui->PriorityBox->currentText();
    QString project =  _projectDataService.getProjectTitle(projId);
    QString assignee = ui->AssigneeBox->currentText();
    bool result;
    result = _taskDataService.createTask(title, desc, effort, priority, project, taskStates.TodoState(), assignee);

    QMessageBox messageBox;

    if(result){
        qDebug() << "Added Task!";
        messageBox.setText("Added Task!");
        messageBox.exec();
        emit addedItem();
        this->hide();
        ui->Title->setText("");
        ui->Description->setPlainText("");
        ui->EffortBox->setCurrentIndex(0);
        ui->PriorityBox->setCurrentIndex(0);
        //ui->ProjectBox->setCurrentIndex(0);
    }
    else{
        messageBox.critical(0,"Error","There was an error when creating the task, please try again!");
    }
}

//void NewTaskForm::populateProjectBox(){
//    QSqlQuery q;
//    q.prepare("SELECT * FROM projects WHERE projects.manager = :usr");
//    q.bindValue(":usr", usr.GetCurrentUserEmail());
//    if(q.exec()){
//        int count = 0;
//        while(q.next()){
//            ui->ProjectBox->insertItem(count, q.value(1).toString());
//            count++;
//        }
//    }
//}

NewTaskForm::~NewTaskForm()
{
    delete ui;
}


