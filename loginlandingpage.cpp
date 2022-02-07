#include "loginlandingpage.h"
#include "ui_loginlandingpage.h"

LoginLandingPage::LoginLandingPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginLandingPage)
{
    ui->setupUi(this);

    QSqlQuery q;
    q.prepare("SELECT * FROM projects");
    if(q.exec()){
        QPushButton *projectBtn;
        int count = 0;
        while(q.next()){
            projectBtn = new QPushButton(q.value(1).toString());
            connect(projectBtn, SIGNAL(clicked()), this, SLOT(button_pushed()));
            ui->verticalLayout->addWidget(projectBtn);
            count++;
        }
    }

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

LoginLandingPage::~LoginLandingPage()
{
    delete ui;
}
