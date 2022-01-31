#include "newtaskform.h"
#include "ui_newtaskform.h"

NewTaskForm::NewTaskForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTaskForm)
{
    ui->setupUi(this);
    QStringList effortPoints = (QStringList()<<"1"<<"2"<<"3"<<"5"<<"8"<<"10");
    QStringList priority = (QStringList()<<"Minor"<<"Medium"<<"Major");
    ui->EffortBox->addItems(effortPoints);
    ui->PriorityBox->addItems(priority);
    connect(ui->CreateTaskBtn, SIGNAL(released()), this, SLOT(onCreateTaskBtnPressed()));
}

QString getTime(){
    time_t now = time(0);
    tm* localtm = localtime(&now);
    std::string localTime = asctime(localtm);
    QString qTime = QString::fromStdString(localTime);
    return qTime;
}

void NewTaskForm::onCreateTaskBtnPressed(){
    QSqlQuery q;
    q.prepare( "INSERT INTO tasks (title, description, effort, priority, created) "
            "VALUES (:tle, :desc, :eff, :pri, :crted)");
    q.bindValue(":tle", ui->Title->text());
    q.bindValue(":desc", ui->Description->toPlainText());
    q.bindValue(":eff", ui->EffortBox->itemData(ui->EffortBox->currentIndex()));
    q.bindValue(":pri", ui->PriorityBox->itemData(ui->PriorityBox->currentIndex()));
    q.bindValue(":crted", getTime());

    QMessageBox messageBox;

    if(q.exec()){
        qDebug() << "Added Task!";
        messageBox.setText("Added Task!");
        messageBox.exec();
        emit addedItem();
        this->hide();
    }
    else{
        qDebug() << q.lastError().text();
        messageBox.critical(0,"Error","There was an error when creating the task, please try again!");
    }
}

NewTaskForm::~NewTaskForm()
{
    delete ui;
}


