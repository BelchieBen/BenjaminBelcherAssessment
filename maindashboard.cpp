#include "maindashboard.h"
#include "ui_maindashboard.h"

MainDashboard::MainDashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDashboard)
{
    ui->setupUi(this);
    connect(ui->CreateTask, SIGNAL(released()), this, SLOT(openCreateTask()));
    connect(ui->CreateProjectBtn, SIGNAL(released()), this, SLOT(openCreateProject()));
    connect(&newTask, SIGNAL(addedItem()), this, SLOT(loadTasks()));
    ui->TaskList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->TaskList, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(showContextMenu(QPoint)));
    loadTasks();
}

void MainDashboard::showContextMenu(const QPoint &pos){
    QPoint globalPos = ui->TaskList->mapToGlobal(pos);

    QMenu editMenu;
    editMenu.addAction("Move to", this, SLOT(moveTask()));
    editMenu.addAction("Delete", this, SLOT(deleteTask()));

    editMenu.exec(globalPos);
}

void MainDashboard::openCreateTask(){
    newTask.setModal(true);
    newTask.exec();
}

void MainDashboard::loadTasks(){
    ui->TaskList->clear();
    QSqlQuery q;
    q.prepare("SELECT * FROM tasks");
    if(q.exec()){
        while(q.next()){
            QListWidget *taskList = ui->TaskList;
            taskList->setItemDelegate(new TaskDelegate(taskList));
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(Qt::DisplayRole, q.value(1).toString());
            item->setData(Qt::UserRole + 1, q.value(2).toString());
            taskList->addItem(item);
        }
    }
}

void MainDashboard::openCreateProject(){
    newProject.setModal(true);
    newProject.exec();
}

void MainDashboard::onAddTestTaskClicked(){


}

MainDashboard::~MainDashboard()
{
    delete ui;
}
