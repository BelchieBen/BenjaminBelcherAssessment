#include "taskdetails.h"
#include "ui_taskdetails.h"

TaskDetails::TaskDetails(QWidget *parent, QListWidgetItem *item) :
    QDialog(parent),
    ui(new Ui::TaskDetails)
{
    ui->setupUi(this);
    this->task = item;
    populateTaskDetails();
}

void TaskDetails::populateTaskDetails(){
    ui->TaskTitle->setText(task->text());
    int taskId = _taskDataService.getTaskId(task->text());
    Task currentTask = _taskDataService.findTaskById(taskId);
    ui->Description->setText(currentTask.returnDescription());
    ui->Priority->setText(currentTask.returnPriority());
    ui->Effort->setText(currentTask.returnEffort());
}

TaskDetails::~TaskDetails()
{
    delete ui;
}
