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
