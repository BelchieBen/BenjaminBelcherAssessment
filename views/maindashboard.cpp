#include "views/maindashboard.h"
#include "ui_maindashboard.h"



MainDashboard::MainDashboard(QWidget *parent, int projectId) :
    QDialog(parent),
    ui(new Ui::MainDashboard)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(&profile);
    this->projId = projectId;
    QString tle = _projDataService.getProjectTitle(projId);
    ui->BoardTitle->setText(tle);
    createManagerBtns();

    connect(this, SIGNAL(movedItem()), this, SLOT(loadTasks()));
    connect(ui->ProjectSettings, SIGNAL(released()), this, SLOT(openProjectSettings()));
    connect(ui->OtherProjectsBtn, SIGNAL(released()), this, SLOT(openProjectsDialog()));
    connect(ui->ProfileBtn, SIGNAL(released()), this, SLOT(openProfilePage()));
    connect(&profile, SIGNAL(returnToDashboard()), this, SLOT(returnToMainDashboardFromProfile()));

    loadTasks();
    createListMenus();
}

void MainDashboard::openCreateTask(){
    QWidget *nullWd = nullptr;
    NewTaskForm newTask(nullWd, projId);
    connect(&newTask, SIGNAL(addedItem()), this, SLOT(loadTasks()));
    newTask.setModal(true);
    newTask.exec();
}

void MainDashboard::loadTasks(){
    clearLists();
    QString tle = _projDataService.getProjectTitle(projId);
    QSqlQuery q;
    q.prepare("SELECT * FROM tasks LEFT JOIN task_users on tasks.id = task_users.task_id WHERE project = :title");
    q.bindValue(":title", tle);
    if(q.exec()){
        int count = 0;
        while(q.next()){
            QString state = q.value(7).toString();
            int uId = q.value(8).toInt();
            QString title = q.value(1).toString();
            QString description = q.value(2).toString();
            populateLists(state, title, description, usr.returnEmail(uId));
            count ++;
        }

        if(count == 0){
            qDebug() << "No tasks found";
        }
        else if(count >= 1){
            qDebug() << "Found some tasks";
        }
    }
}

void MainDashboard::openCreateProject(){
    newProject.setModal(true);
    newProject.exec();
}

void MainDashboard::moveTaskToInProgress(){
    QListWidget *list = ui->TaskList;
    TaskDataService _taskDataService;
    for(int i=0; i<list->selectedItems().size(); i++){
        QListWidgetItem *task = list->takeItem(list->currentRow());
        if(_taskDataService.updateTaskStatus(*task, taskStates.InProgressState())){
            emit movedItem();
        }
    }
}

void MainDashboard::moveTaskToReview(){
    QListWidget *list = ui->InProgressList;
    TaskDataService _taskDataService;
    for(int i=0; i<list->selectedItems().size(); i++){
        QListWidgetItem *task = list->takeItem(list->currentRow());
        if(_taskDataService.updateTaskStatus(*task, taskStates.InReviewState())){
            emit movedItem();
        }
    }
}

void MainDashboard::moveTaskToDone(){
    QListWidget *list = ui->ReviewList;
    TaskDataService _taskDataService;
    for(int i=0; i<list->selectedItems().size(); i++){
        QListWidgetItem *task = list->takeItem(list->currentRow());
        if(_taskDataService.updateTaskStatus(*task, taskStates.InDoneState())){
            emit movedItem();
        }
    }
}

void MainDashboard::assignToMe(){
    int taskId;
    int uId;
    QString email = usr.GetCurrentUserEmail();
    QString test = ui->TaskList->currentItem()->text();
    uId = usr.getUserId(email);
    taskId = _taskDataService.getTaskId(test);
    if(_taskDataService.addUserToTask(taskId, uId)){
            qDebug() << "Assigned user to task from menu";
            loadTasks();
    }
    else{
        _messageBox.critical(0,"Error", "Someone is already assigned to that task!");
    }

}

void MainDashboard::createListMenus(){
    auto MoveToInProgress = new QAction("Move to in progress", this);
    auto AssignUser = new QAction("Assign to me", this);
    connect(MoveToInProgress, SIGNAL(triggered()), this, SLOT(moveTaskToInProgress()));
    connect(AssignUser, SIGNAL(triggered()), this, SLOT(assignToMe()));
    ui->TaskList->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->TaskList->addActions({MoveToInProgress, AssignUser});

    auto MoveToReview = new QAction("Move to review", this);
    connect(MoveToReview, SIGNAL(triggered()), this, SLOT(moveTaskToReview()));
    ui->InProgressList->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->InProgressList->addActions({MoveToReview});

    auto MoveToDone = new QAction("Move to done", this);
    connect(MoveToDone, SIGNAL(triggered()), this, SLOT(moveTaskToDone()));
    ui->ReviewList->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->ReviewList->addActions({MoveToDone});
}

void MainDashboard::populateLists(QString state, QString title, QString description, QString user){
    QListWidget *todoList = ui->TaskList;
    QListWidget *inProgressList = ui->InProgressList;
    QListWidget *reviewList = ui->ReviewList;
    QListWidget *doneList = ui->DoneList;
    if(user == ""){
        user = "Unassigned";
    }
    QFont sansFont("Helvetica [Cronyx]", 22);
    if(state == "Todo"){
        todoList->setItemDelegate(new TaskDelegate(todoList));
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DisplayRole, title);
        item->setData(Qt::UserRole + 1, description);
        item->setData(Qt::ToolTipRole, user);
        todoList->addItem(item);
    }

    if(state == "In Progress"){
        inProgressList->setItemDelegate(new TaskDelegate(inProgressList));
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DisplayRole, title);
        item->setData(Qt::UserRole + 1, description);
        item->setData(Qt::ToolTipRole, user);
        inProgressList->addItem(item);
    }

    if(state == "In Review"){
        reviewList->setItemDelegate(new TaskDelegate(reviewList));
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DisplayRole, title);
        item->setData(Qt::UserRole + 1, description);
        item->setData(Qt::ToolTipRole, user);
        reviewList->addItem(item);
    }

    if(state == "Done"){
        doneList->setItemDelegate(new TaskDelegate(doneList));
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DisplayRole, title);
        item->setData(Qt::UserRole + 1, description);
        item->setData(Qt::ToolTipRole, user);
        doneList->addItem(item);
    }
}

void MainDashboard::clearLists(){
    ui->TaskList->clear();
    ui->InProgressList->clear();
    ui->ReviewList->clear();
    ui->DoneList->clear();
}

void MainDashboard::onAddTestTaskClicked(){


}

void MainDashboard::searchCurrentBoard(){
    QSqlQuery q;
    q.prepare("SELECT * FROM tasks WHERE title LIKE %:search%");
    q.bindValue(":search", ui->SearchCurrentBoard->text());
    if(q.exec()){


        while(q.next()){

        }
    }
    else{
        QMessageBox _msgBox;
        _msgBox.critical(0, "Error", "Invalid search, try again");
        _msgBox.setFixedSize(500,200);
    }
}

void MainDashboard::openProjectsDialog(){
    LoginLandingPage otherProjects;

    otherProjects.setModal(true);
    otherProjects.exec();
}

MainDashboard::~MainDashboard()
{
    delete ui;
}

void MainDashboard::on_SearchCurrentBoard_textChanged(const QString &arg1)
{
    clearLists();
    QSqlQuery q;
    q.prepare("SELECT * FROM tasks INNER JOIN task_users on tasks.id = task_users.task_id WHERE title LIKE '%'||:search||'%' AND project = :proj");
    q.bindValue(":proj", ui->BoardTitle->text());
    q.bindValue(":search", ui->SearchCurrentBoard->text());
    if(q.exec()){
        while(q.next()){
            QString state = q.value(7).toString();
            int uId = q.value(8).toInt();
            QString title = q.value(1).toString();
            QString description = q.value(2).toString();
            populateLists(state, title, description, usr.returnEmail(uId));
        }
    }
    else
        qDebug()<<q.lastError().text();
}

void MainDashboard::openProjectSettings(){
    QWidget *nullWd = nullptr;
    ProjectSettingsPage _projectSettings(nullWd, projId);
    _projectSettings.setModal(true);
    _projectSettings.exec();
}

void MainDashboard::createManagerBtns(){
    if(usr.getUserRole() == roles.getRole("manager")){
        QPushButton *CreateTask = new QPushButton("Create Task");
        connect(CreateTask, SIGNAL(released()), this, SLOT(openCreateTask()));
        QPushButton *CreateProjectBtn = new QPushButton("Create Project");
        connect(CreateProjectBtn, SIGNAL(released()), this, SLOT(openCreateProject()));
        ui->sidebarLayout->addWidget(CreateTask);
        ui->sidebarLayout->addWidget(CreateProjectBtn);
    }
}

void MainDashboard::returnToMainDashboardFromProfile(){
    ui->stackedWidget->setCurrentIndex(0);
}

void MainDashboard::openProfilePage(){

    ui->stackedWidget->setCurrentIndex(1);
    user u = usr.getCurrentUser();
    profile.populateTreeWidget(u);
}

void MainDashboard::openTaskDetails(QListWidgetItem *item){
    QWidget *nullWd = nullptr;
    TaskDetails taskDetails(nullWd, item);
    taskDetails.setModal(true);
    taskDetails.exec();
}


void MainDashboard::on_TaskList_itemDoubleClicked(QListWidgetItem *item)
{
    openTaskDetails(item);
}


void MainDashboard::on_InProgressList_itemDoubleClicked(QListWidgetItem *item)
{
    openTaskDetails(item);
}


void MainDashboard::on_ReviewList_itemDoubleClicked(QListWidgetItem *item)
{
    openTaskDetails(item);
}


void MainDashboard::on_DoneList_itemDoubleClicked(QListWidgetItem *item)
{
    openTaskDetails(item);
}

