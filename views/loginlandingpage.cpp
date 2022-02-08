#include "loginlandingpage.h"
#include "ui_loginlandingpage.h"

LoginLandingPage::LoginLandingPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginLandingPage)
{
    ui->setupUi(this);

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

void LoginLandingPage::loadProjects(){
    QSqlQuery q;
    q.prepare("SELECT * FROM projects INNER JOIN project_users ON project_users.project = projects.id WHERE project_users.user = :usr");
    q.bindValue(":usr", usr.GetCurrentUserEmail());
    if(q.exec()){
        QPushButton *projectBtn;
        int count = 0;
        while(q.next()){
            projectBtn = new QPushButton(q.value(1).toString());
            connect(projectBtn, SIGNAL(clicked()), this, SLOT(button_pushed()));
            ui->verticalLayout->addWidget(projectBtn);
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
        connect(newProjBtn, SIGNAL(clicked()), this, SLOT(createprojectBtnClicked()));
        ui->verticalLayout->addWidget(newProjBtn);
    }
}

LoginLandingPage::~LoginLandingPage()
{
    delete ui;
}
