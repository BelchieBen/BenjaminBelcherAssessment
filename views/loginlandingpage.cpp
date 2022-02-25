#include "loginlandingpage.h"
#include "ui_loginlandingpage.h"

LoginLandingPage::LoginLandingPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginLandingPage)
{
    ui->setupUi(this);
    ui->ButtonsLayout->layout();
    connect(&newproject, SIGNAL(projectCreated()), this, SLOT(loadProjects()));
    addCreateProjectBtn();
    loadProjects();
}

void LoginLandingPage::button_pushed(){
    ProjectDataService _projectDataService;

    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
         if (pButton) // this is the type we expect
         {
             QString buttonText = pButton->text();
             QWidget *nullWd = nullptr;
             int projectId = _projectDataService.getProject(buttonText);
             this->hide();
             MainDashboard dashboard(nullWd, projectId);
             dashboard.setModal(true);
             dashboard.showFullScreen();
             dashboard.setWindowFlags(Qt::Window);
             dashboard.exec();
         }
}

void LoginLandingPage::createprojectBtnClicked(){
    newproject.setModal(true);
    newproject.exec();
}

void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        QWidget* widget;
        if (  (deleteWidgets)
              && (widget = item->widget())  ) {
            delete widget;
        }
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }
}

void LoginLandingPage::loadProjects(){
    clearLayout(ui->ButtonsLayout);
    QSqlQuery q;
    q.prepare("SELECT * FROM projects INNER JOIN project_users ON project_users.project = projects.id WHERE project_users.user = :usr");
    q.bindValue(":usr", usr.GetCurrentUserEmail());
    if(q.exec()){
        QPushButton *projectBtn;
        int count = 0;
        while(q.next()){
            projectBtn = new QPushButton(q.value(1).toString());
            projectBtn->setStyleSheet("background-color: #2F4051; color: rgb(255, 255, 255); border-radius:8px; padding:4px");
            connect(projectBtn, SIGNAL(clicked()), this, SLOT(button_pushed()));
            ui->ButtonsLayout->addWidget(projectBtn);
            count++;
        }

        if(count == 0){
            ui->label->setText("Looks like you have no active projects");
        }
    }
}

void LoginLandingPage::addCreateProjectBtn(){
    if(usr.getUserRole() == roles.getRole("manager")){
        QPushButton *newProjBtn = new QPushButton("Create a new project");
        newProjBtn->setStyleSheet("background-color: #056D78; color: rgb(255, 255, 255); border-radius:8px; padding:4px");
        connect(newProjBtn, SIGNAL(clicked()), this, SLOT(createprojectBtnClicked()));
        ui->CreateButtonLayout->addWidget(newProjBtn);
    }
}

LoginLandingPage::~LoginLandingPage()
{
    delete ui;
}
