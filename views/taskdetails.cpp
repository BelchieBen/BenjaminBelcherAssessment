#include "taskdetails.h"
#include "ui_taskdetails.h"

TaskDetails::TaskDetails(QWidget *parent, QListWidgetItem *item) :
    QDialog(parent),
    ui(new Ui::TaskDetails)
{
    ui->setupUi(this);
    this->task = item;
    populateTaskDetails();
    this->taskId = _taskDataService.getTaskId(item->text());
    QStringList effortPoints = (QStringList()<<"1"<<"2"<<"3"<<"5"<<"8"<<"10");
    QStringList priority = (QStringList()<<"Minor"<<"Medium"<<"Major");
    ui->EffortBox->addItems(effortPoints);
    ui->PriorityBox->addItems(priority);
    populateCommentBox();
    createManagerBtns();
    connect(ui->CommentBtn, SIGNAL(released()), this, SLOT(addCommentToTask()));
    connect(ui->SaveBtn, SIGNAL(released()), this, SLOT(saveTask()));
    connect(this, SIGNAL(updatedTask()), this, SLOT(populateTaskDetails()));
}

TaskDetails::TaskDetails(QWidget *parent, Task *item) :
    QDialog(parent),
    ui(new Ui::TaskDetails)
{
    ui->setupUi(this);
    this->taskT = item;
    populateTaskDetailsUsingModel();
    this->taskId = _taskDataService.getTaskId(item->returnTitle());
    populateCommentBox();
    connect(ui->CommentBtn, SIGNAL(released()), this, SLOT(addCommentToTask()));
}

void TaskDetails::populateTaskDetails(){
    ui->TaskTitle->setText(task->text());
    int taskId = _taskDataService.getTaskId(task->text());
    Task currentTask = _taskDataService.findTaskById(taskId);
    ui->Description->setText(currentTask.returnDescription());
    ui->Priority->setText(currentTask.returnPriority());
    ui->Effort->setText(currentTask.returnEffort());
}

void TaskDetails::populateTaskDetailsUsingModel(){
    ui->TaskTitle->setText(taskT->returnTitle());
    int taskId = _taskDataService.getTaskId(taskT->returnTitle());
    Task currentTask = _taskDataService.findTaskById(taskId);
    ui->Description->setText(currentTask.returnDescription());
    ui->Priority->setText(currentTask.returnPriority());
    ui->Effort->setText(currentTask.returnEffort());
}

void TaskDetails::createManagerBtns()
{
    QString email;
    QString taskTitle = task->data(0).toString();
    if(taskTitle != ""){
        int taskId = _taskDataService.getTaskId(taskTitle);
        Task t = _taskDataService.findTaskById(taskId);
        email = usr.returnEmail(t.returnUser());
    }
    else{
        email = usr.returnEmail(taskT->returnUser());
    }

    if(usr.getUserRole() == roles.getRole("manager") || usr.GetCurrentUserEmail() == email){
        QPushButton *EditTask = new QPushButton("Edit Task");
        EditTask->setStyleSheet("background-color:rgb(227, 0, 114); color: rgb(255, 255, 255); border-radius:8px; padding-top:4px; padding-bottom:4px; padding-left:25px; padding-right:25px;");
        connect(EditTask, SIGNAL(released()), this, SLOT(editTask()));
        ui->EditLayout->insertWidget(0,EditTask);
    }
}

void TaskDetails::editTask()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void TaskDetails::saveTask()
{
    if(_taskDataService.updateTaskDetails(taskId, ui->PriorityBox->currentText(), ui->EffortBox->currentText(), ui->DescriptionTxtBox->toPlainText())){
        emit updatedTask();
        ui->stackedWidget->setCurrentIndex(0);
    }
    else{
         _messageBox.critical(0,"Error", "Could not update the task");
    }
}

void TaskDetails::addCommentToTask(){
    QString comment = ui->CommentInput->text();
    if(_taskDataService.addCommentToTask(comment, taskId)){
        ui->CommentInput->clear();
        populateCommentBox();
    }
    else{
        _messageBox.critical(0,"Error", "Could not add that comment");
    }
}

void TaskDetails::populateCommentBox(){
    ui->listWidget->clear();
    QListWidget *commentList = ui->listWidget;
    QList<TaskComment> comments = _taskDataService.getTaskComments(taskId);
    QList<TaskComment>::iterator i;
    for(i = comments.begin(); i != comments.end(); i++){
        QString dateStr = i->getPosted().toString(Qt::TextDate);
        QString email = usr.returnEmail(i->getUserId());
//        QDateTime localDate= i->getPosted().toLocalTime();
//        list = commentDate.split("T");
//        QString joinedString = list.join(" ");
        commentList->setItemDelegate(new CommentDelegate(commentList));
        QListWidgetItem *comment = new QListWidgetItem();
        comment->setData(Qt::DisplayRole, i->getComment());
        comment->setData(Qt::UserRole + 1, dateStr);
        comment->setData(Qt::ToolTipRole, email);
        commentList->addItem(comment);
    }
}

TaskDetails::~TaskDetails()
{
    delete ui;
}
