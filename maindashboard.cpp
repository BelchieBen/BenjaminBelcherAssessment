#include "maindashboard.h"
#include "ui_maindashboard.h"

MainDashboard::MainDashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDashboard)
{
    ui->setupUi(this);
    connect(ui->addItm, SIGNAL(released()), this, SLOT(onAddTestTaskClicked()));
}

void MainDashboard::onAddTestTaskClicked(){
    QListWidget *taskList = ui->TaskList;
    taskList->setItemDelegate(new TaskDelegate(taskList));
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::DisplayRole, "Title");
    item->setData(Qt::UserRole + 1, "Description");
    taskList->addItem(item);
}

MainDashboard::~MainDashboard()
{
    delete ui;
}
