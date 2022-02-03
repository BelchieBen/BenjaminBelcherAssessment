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
    //ui->TaskList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->InProgressList->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(ui->TaskList, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(showContextMenu(QPoint)));
    connect(ui->InProgressList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showInProgressMenu(QPoint)));
    loadTasks();

    auto actMove = new QAction("Move", this);
    connect(actMove, SIGNAL(triggered()), this, SLOT(moveTask()));
    ui->TaskList->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->TaskList->addActions({actMove});

    taskList = ui->TaskList;
    inProgress = ui->InProgressList;
}

void MainDashboard::showContextMenu(const QPoint &pos){
    QPoint globalPos = ui->TaskList->mapToGlobal(pos);

    QMenu editMenu;
    editMenu.addAction("Move to in progress", this, SLOT(moveTask(&ui->TaskList)));
    editMenu.addAction("Delete", this, SLOT(deleteTask()));

    editMenu.exec(globalPos);
}

void MainDashboard::showInProgressMenu(const QPoint &pos){
    QPoint globalPos = ui->InProgressList->mapToGlobal(pos);


    QMenu editMenu;
    editMenu.addAction("Move to review", this, SLOT(moveTask(inProgress)));
    editMenu.exec(globalPos);
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

void MainDashboard::moveTask(){
    QListWidget *list = ui->TaskList;
    TaskDataService _taskDataService;
    for(int i=0; i<list->selectedItems().size(); i++){
        QListWidgetItem *task = list->takeItem(list->currentRow());
        if(_taskDataService.updateTaskStatus(*task)){
            emit movedItem();
        }
    }
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
