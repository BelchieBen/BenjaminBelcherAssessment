#include "searchtasksallprojectsdialog.h"
#include "ui_searchtasksallprojectsdialog.h"

SearchTasksAllProjectsDialog::SearchTasksAllProjectsDialog(QWidget *parent, QList<Task> tks) :
    QDialog(parent),
    ui(new Ui::SearchTasksAllProjectsDialog)
{
    ui->setupUi(this);
    this->tasks = tks;
    connect(ui->CloseBtn, SIGNAL(released()), this, SLOT(closeDialog()));
    createTaskWidget();
}

void SearchTasksAllProjectsDialog::createTaskWidget(){
    QList<Task>::iterator i;
    int count = 0;
    for(i = tasks.begin(); i != tasks.end(); ++i){
        QWidget *taskW = new QWidget();
        taskW->setMaximumSize(1000000, 300);
        taskW->setStyleSheet("background-color: #dbdbdb; border-radius:10px");
        QVBoxLayout *taskLayout = new QVBoxLayout(taskW);
        QLabel *title = new QLabel(taskW);
        QLabel *description = new QLabel(taskW);
        QLabel *effort = new QLabel(taskW);
        QLabel *priority = new QLabel(taskW);
        QLabel *created = new QLabel(taskW);
        QLabel *project = new QLabel(taskW);
        QLabel *state = new QLabel(taskW);
        QLabel *userId = new QLabel(taskW);
        QPushButton *open = new QPushButton("Open");
        open->setProperty("TaskName", i->returnTitle());
        connect(open, SIGNAL(released()), this, SLOT(openTask()));

        auto *line = new QFrame;
        line->setFrameShape(QFrame::HLine);
        line->setFixedHeight(1);
        line->setStyleSheet("background-color:#465564");

        title->setText(i->returnTitle());
        title->setFont(QFont("Gilroy", 14, QFont::Bold));
        taskLayout->addWidget(title);
        taskLayout->addWidget(line);

        description->setText(i->returnDescription());
        taskLayout->addWidget(description);

        QHBoxLayout *effortLayout = new QHBoxLayout(taskW);
        QLabel *effortLbl = new QLabel(taskW);
        effortLbl->setText("Effort: ");
        effortLbl->setFont(QFont("Gilroy", 11, QFont::Bold));
        effortLayout->addWidget(effortLbl);
        effort->setText(i->returnEffort());
        effortLayout->addWidget(effort);
        effortLayout->addStretch(1);
        taskLayout->addItem(effortLayout);

        QHBoxLayout *priorityLayout = new QHBoxLayout(taskW);
        QLabel *priorityLbl = new QLabel(taskW);
        priorityLbl->setText("Priority: ");
        priorityLbl->setFont(QFont("Gilroy", 11, QFont::Bold));
        priorityLayout->addWidget(priorityLbl);
        priority->setText(i->returnPriority());
        priorityLayout->addWidget(priority);
        priorityLayout->addStretch(1);
        taskLayout->addItem(priorityLayout);

        QHBoxLayout *dateLayout = new QHBoxLayout(taskW);
        QLabel *date = new QLabel(taskW);
        date->setText("Date: ");
        date->setFont(QFont("Gilroy", 11, QFont::Bold));
        dateLayout->addWidget(date);
        created->setText(i->returnCreated());
        dateLayout->addWidget(created);
        dateLayout->addStretch(1);
        taskLayout->addItem(dateLayout);

        QHBoxLayout *projectLayout = new QHBoxLayout(taskW);
        QLabel *projectLbl = new QLabel(taskW);
        projectLbl->setText("Project: ");
        projectLbl->setFont(QFont("Gilroy", 11, QFont::Bold));
        projectLayout->addWidget(projectLbl);
        project->setText(i->returnProject());
        projectLayout->addWidget(project);
        projectLayout->addStretch(1);
        taskLayout->addItem(projectLayout);

        QHBoxLayout *stateLayout = new QHBoxLayout(taskW);
        QLabel *stateLbl = new QLabel(taskW);
        stateLbl->setText("State: ");
        stateLbl->setFont(QFont("Gilroy", 11, QFont::Bold));
        stateLayout->addWidget(stateLbl);
        state->setText(i->returnState());
        stateLayout->addWidget(state);
        stateLayout->addStretch(1);
        taskLayout->addItem(stateLayout);

        QHBoxLayout *userLayout = new QHBoxLayout(taskW);
        QLabel *userLbl = new QLabel(taskW);
        userLbl->setText("Assignee: ");
        userLbl->setFont(QFont("Gilroy", 11, QFont::Bold));
        userLayout->addWidget(userLbl);
        userId->setText(QString::number(i->returnUser()));
        userLayout->addWidget(userId);
        userLayout->addStretch(1);
        taskLayout->addItem(userLayout);

        open->setStyleSheet("color:#056D78");
        taskLayout->addWidget(open);

        ui->TaskList->addWidget(taskW);
        count ++;
    }
    ui->YourSearchReturnedLbl->setText("Your search returned "+QString::number(count)+" results.");
}

void SearchTasksAllProjectsDialog::closeDialog(){
    this->close();
}

void SearchTasksAllProjectsDialog::openTask(){
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    if (pButton) // this is the type we expect
    {
      QVariant taskName = pButton->property("TaskName");
      QString taskTitle = taskName.toString();
      int id = _taskDataService.getTaskId(taskTitle);
      Task t = _taskDataService.findTaskById(id);
      QWidget *nullWd = nullptr;
      TaskDetails details(nullWd, &t);
      details.setModal(true);
      details.exec();
    }
}

SearchTasksAllProjectsDialog::~SearchTasksAllProjectsDialog()
{
    delete ui;
}
