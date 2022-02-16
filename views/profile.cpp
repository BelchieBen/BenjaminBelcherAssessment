#include "profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);
    user u = usr.getCurrentUser();
    ui->WelcomeLbl->setText("Hello "+u.returnFirstname());
    ui->Firstname->setText(u.returnFirstname());
    ui->Surname->setText(u.returnSurname());
    ui->Email->setText(u.returnEmail());
    ui->Role->setText(u.returnRole());
    populateTreeWidget(u);

    connect(ui->MainDashboardBtn, SIGNAL(released()), this, SLOT(returnToMainDashboard()));

}

void Profile::returnToMainDashboard(){
    emit returnToDashboard();
}

void Profile::populateTreeWidget(user u){
    //QList<QList<Task>> UserTasksByProject;
    QList<Task> tasks = _taskDataService.findAllTasksForUser(u.getUserId(u.returnEmail()));
    QList<Task>::iterator i;
    int col = 0;
    int row = 0;
    for(i = tasks.begin(); i != tasks.end(); ++i){
        QWidget *taskW = new QWidget();
        taskW->setStyleSheet("background-color: teal");
        taskW->setMaximumHeight(200);

        QVBoxLayout *taskInfo = new QVBoxLayout(taskW);
        QHBoxLayout *descLayout = new QHBoxLayout(taskW);
        QHBoxLayout *stateLayout = new QHBoxLayout(taskW);
        QHBoxLayout *effortLayout = new QHBoxLayout(taskW);
        QHBoxLayout *priorityLayout = new QHBoxLayout(taskW);
        QHBoxLayout *projectLayout = new QHBoxLayout(taskW);

        QLabel *TaskTitle = new QLabel(taskW);
        QLabel *TaskDescription = new QLabel(taskW);
        QLabel *TaskDescriptionLbl = new QLabel(taskW);
        QLabel *TaskState = new QLabel(taskW);
        QLabel *TaskStateLbl = new QLabel(taskW);
        QLabel *TaskEffort = new QLabel(taskW);
        QLabel *TaskEffortLbl = new QLabel(taskW);
        QLabel *TaskPriority = new QLabel(taskW);
        QLabel *TaskPriorityLbl = new QLabel(taskW);
        QLabel *TaskProject = new QLabel(taskW);
        QLabel *TaskProjectLbl = new QLabel(taskW);

        TaskTitle->setText(i->returnTitle());
        TaskTitle->setFont(QFont( "Lucida Grande", 16, QFont::Bold ));
        taskInfo->addWidget(TaskTitle);

        TaskDescriptionLbl->setText("Description: ");
        TaskDescriptionLbl->setFont(QFont( "Lucida Grande", 11, QFont::Bold ));
        TaskDescription->setText(i->returnDescription());
        TaskDescription->setFont(QFont( "Lucida Grande", 10, QFont::Normal ));
        descLayout->addWidget(TaskDescriptionLbl);
        descLayout->addWidget(TaskDescription);
        descLayout->addStretch(1);
        taskInfo->addItem(descLayout);

        TaskStateLbl->setText("State: ");
        TaskStateLbl->setFont(QFont( "Lucida Grande", 11, QFont::Bold ));
        TaskState->setText(i->returnState());
        TaskState->setFont(QFont( "Lucida Grande", 10, QFont::Normal ));
        stateLayout->addWidget(TaskStateLbl);
        stateLayout->addWidget(TaskState);
        stateLayout->addStretch(1);
        taskInfo->addItem(stateLayout);

        TaskEffortLbl->setText("Effort: ");
        TaskEffortLbl->setFont(QFont( "Lucida Grande", 11, QFont::Bold ));
        TaskEffort->setText(i->returnEffort());
        TaskEffort->setFont(QFont( "Lucida Grande", 10, QFont::Normal ));
        effortLayout->addWidget(TaskEffortLbl);
        effortLayout->addWidget(TaskEffort);
        effortLayout->addStretch(1);
        taskInfo->addItem(effortLayout);

        TaskPriorityLbl->setText("Priority: ");
        TaskPriorityLbl->setFont(QFont( "Lucida Grande", 11, QFont::Bold ));
        TaskPriority->setText(i->returnPriority());
        TaskPriority->setFont(QFont( "Lucida Grande", 10, QFont::Normal ));
        priorityLayout->addWidget(TaskPriorityLbl);
        priorityLayout->addWidget(TaskPriority);
        priorityLayout->addStretch(1);
        taskInfo->addItem(priorityLayout);

        TaskProjectLbl->setText("Project: ");
        TaskProjectLbl->setFont(QFont( "Lucida Grande", 11, QFont::Bold ));
        TaskProject->setText(i->returnProject());
        TaskProject->setFont(QFont( "Lucida Grande", 10, QFont::Normal ));
        projectLayout->addWidget(TaskProjectLbl);
        projectLayout->addWidget(TaskProject);
        projectLayout->addStretch(1);
        taskInfo->addItem(projectLayout);

        taskInfo->addStretch(1);

        if(col>2){
            col =0;
            row ++;
        }

        ui->MyTasks->addWidget(taskW, row, col);
        col ++;

    }
    ui->verticalLayout->addStretch(1);
//    QSqlQuery q;
//    q.prepare("SELECT * FROM projects INNER JOIN project_users on projects.id = project_users.project WHERE project_users.user = :usr");
//    q.bindValue(":usr", u.returnEmail());
//    QString projectTitle;
//    if(q.exec()){
//        while(q.next()){
//            projectTitle = q.value(1).toString();
//            QList<Task> tasks = _taskDataService.findAllTasksForUser(u.getUserId(u.returnEmail()));
//            UserTasksByProject.append(tasks);
//        }
//    }

//    QTreeWidget *tree = ui->treeWidget;
//    delete tree->takeTopLevelItem(0);
//    QTreeWidgetItem *topLevel = new QTreeWidgetItem();
//    topLevel->setText(0, "This the projects col");
//    for (int i=0; i<5 ;i++ ) {
//        QTreeWidgetItem *item = new QTreeWidgetItem();
//        item->setText(i, "Task "+ QString::number(i+1));
//        topLevel->addChild(item);
//    }
//    tree->setColumnCount(5);
//    QList<QString> headers;
//    headers.append("Testing1");
//    headers.append("Testing2");
//    headers.append("Testing3");
//    headers.append("Testing4");
//    headers.append("Testing5");
//    tree->setHeaderLabels(headers);

//    for(int i=0; i<5; i++)
//    {
//        QTreeWidgetItem * item = new QTreeWidgetItem();
//        item->setText(i,"top-level " + QString::number(i+1));
//        tree->addTopLevelItem(item);
//    }
}

Profile::~Profile()
{
    delete ui;
}
