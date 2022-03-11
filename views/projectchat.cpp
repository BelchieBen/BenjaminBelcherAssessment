#include "projectchat.h"
#include "ui_projectchat.h"

ProjectChat::ProjectChat(QWidget *parent, int projId) :
    QWidget(parent),
    ui(new Ui::ProjectChat)
{
    ui->setupUi(this);
    this->projectId = projId;
    QString projectTitle = _projDataService.getProjectTitle(projectId);

    completeProjectBtn = new QPushButton("Mark project as complete");
    ui->BackToProjectBtn->setText("Back to dashboard");
    ui->TitleLbl->setText(projectTitle);
    ui->projectProgress->setStyleSheet("QProgressBar::chunk {background: #005936;}");
    connect(ui->BackToProjectBtn, SIGNAL(released()), this, SLOT(returnToProject()));
    connect(ui->SendBtn, SIGNAL(released()), this, SLOT(sendMessageBtnPressed()));
    loadMessages();
    loadProjectUsers();
    setProgressBarValue();
    if(_projDataService.isProjectComplete(projectId)){
        completeProjectBtn->setEnabled(false);
        completeProjectBtn->setStyleSheet("background-color: #5D6977; color: rgb(255, 255, 255); border-radius:8px; padding:4px");
    }
}

void ProjectChat::returnToProject(){
    emit returnToProjectDashboard();
}

void ProjectChat::setProgressBarValue(){
     ui->projectProgress->setValue(_projDataService.calculateProjectProgress(_projDataService.getProjectTitle(projectId)));
     if(ui->projectProgress->value() == 100){
         if(usr.getUserRole() == roles.getRole("manager")){ 
             connect(completeProjectBtn, SIGNAL(released()), this, SLOT(markProjectAsComplete()));
             completeProjectBtn->setStyleSheet("background-color: #005936; color: rgb(255, 255, 255); border-radius:8px; padding:4px");
             ui->widget->layout()->addWidget(completeProjectBtn);
         }
     }
}

void ProjectChat::markProjectAsComplete()
{
    if(_projDataService.updateProjectStatus(projectId, states.getState("Completed"))){
        QList<QString> currentUsers = _projDataService.getCurrentUsers(projectId);
        QList<QString>::iterator i;
        for(i = currentUsers.begin(); i != currentUsers.end(); ++i){
            EmailService* smtp = new EmailService(details.getUsername(), details.getPassword(), details.getServerAddress(), details.getPort());
            smtp->sendMail(details.getUsername(), *i, ui->TitleLbl->text()+" is now complete!", "This project has been marked as complete by your project manager.");
        }
        completeProjectBtn->setEnabled(false);
        completeProjectBtn->setStyleSheet("background-color: #5D6977; color: rgb(255, 255, 255); border-radius:8px; padding:4px");
        emit projectComplete();
    }
}

void ProjectChat::sendMessageBtnPressed(){
    user curUsr = usr.getCurrentUser();
    if(_projDataService.sendProjectMessage(projectId, ui->MessageTitle->text(), ui->MessageBody->toPlainText(), curUsr.getUserId(curUsr.returnEmail()))){
        ui->MessageTitle->clear();
        ui->MessageBody->clear();
        loadMessages();
    }
}

void ProjectChat::loadMessages(){
    QListWidget *messagesList = ui->Messages;
    messagesList->clear();
    QList<ProjectMessage> messages = _projDataService.fetchProjectMessages(projectId);
    QList<ProjectMessage>::iterator i;
    for(i = messages.begin(); i != messages.end(); ++i){
        QString email = usr.returnEmail(i->getAuthor());
        messagesList->setItemDelegate(new MessageDelegate(messagesList));
        QListWidgetItem *message = new QListWidgetItem();
        message->setData(Qt::DisplayRole, i->getMessageTitle());
        message->setData(Qt::DecorationRole, i->getMessageBody());
        message->setData(Qt::UserRole + 1, i->getCreated());
        message->setData(Qt::ToolTipRole, email);
        messagesList->addItem(message);
    }
}

void ProjectChat::loadProjectUsers(){
    QList<QString> currentUsers = _projDataService.getCurrentUsers(projectId);
    ui->projectMembersList->addItems(currentUsers);
}

ProjectChat::~ProjectChat()
{
    delete ui;
}
