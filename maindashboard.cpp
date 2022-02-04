#include "maindashboard.h"
#include "ui_maindashboard.h"
#include "taskdataservice.h"



MainDashboard::MainDashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDashboard)
{
    ui->setupUi(this);

    connect(ui->CreateTask, SIGNAL(released()), this, SLOT(openCreateTask()));
    connect(ui->CreateProjectBtn, SIGNAL(released()), this, SLOT(openCreateProject()));
    connect(&newTask, SIGNAL(addedItem()), this, SLOT(loadTasks()));
    connect(this, SIGNAL(movedItem()), this, SLOT(loadTasks()));

    loadTasks();
    createListMenus();
}

void MainDashboard::openCreateTask(){
    newTask.setModal(true);
    newTask.exec();
}

void MainDashboard::loadTasks(){
    clearLists();
    QSqlQuery q;
    q.prepare("SELECT * FROM tasks");
    if(q.exec()){
        while(q.next()){
            QString state = q.value(7).toString();
            QString title = q.value(1).toString();
            QString description = q.value(2).toString();
            populateLists(state, title, description);
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

void MainDashboard::createListMenus(){
    auto MoveToInProgress = new QAction("Move to in progress", this);
    connect(MoveToInProgress, SIGNAL(triggered()), this, SLOT(moveTaskToInProgress()));
    ui->TaskList->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->TaskList->addActions({MoveToInProgress});

    auto MoveToReview = new QAction("Move to review", this);
    connect(MoveToReview, SIGNAL(triggered()), this, SLOT(moveTaskToReview()));
    ui->InProgressList->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->InProgressList->addActions({MoveToReview});

    auto MoveToDone = new QAction("Move to done", this);
    connect(MoveToDone, SIGNAL(triggered()), this, SLOT(moveTaskToDone()));
    ui->ReviewList->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->ReviewList->addActions({MoveToDone});
}

void MainDashboard::populateLists(QString state, QString title, QString description){
    QListWidget *todoList = ui->TaskList;
    QListWidget *inProgressList = ui->InProgressList;
    QListWidget *reviewList = ui->ReviewList;
    QListWidget *doneList = ui->DoneList;
    if(state == "Todo"){
        todoList->setItemDelegate(new TaskDelegate(todoList));
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DisplayRole, title);
        item->setData(Qt::UserRole + 1, description);
        todoList->addItem(item);
    }

    if(state == "In Progress"){
        inProgressList->setItemDelegate(new TaskDelegate(inProgressList));
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DisplayRole, title);
        item->setData(Qt::UserRole + 1, description);
        inProgressList->addItem(item);
    }

    if(state == "In Review"){
        reviewList->setItemDelegate(new TaskDelegate(reviewList));
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DisplayRole, title);
        item->setData(Qt::UserRole + 1, description);
        reviewList->addItem(item);
    }

    if(state == "Done"){
        doneList->setItemDelegate(new TaskDelegate(doneList));
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DisplayRole, title);
        item->setData(Qt::UserRole + 1, description);
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

MainDashboard::~MainDashboard()
{
    delete ui;
}
