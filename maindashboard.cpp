#include "maindashboard.h"
#include "ui_maindashboard.h"

MainDashboard::MainDashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDashboard)
{
    ui->setupUi(this);
    connect(ui->CreateTask, SIGNAL(released()), this, SLOT(openCreateTask()));
    connect(&newTask, SIGNAL(addedItem()), this, SLOT(loadTasks()));
    loadTasks();
}

void MainDashboard::openCreateTask(){
    newTask.setModal(true);
    newTask.exec();
}

void MainDashboard::loadTasks(){
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

void MainDashboard::onAddTestTaskClicked(){


}

MainDashboard::~MainDashboard()
{
    delete ui;
}
