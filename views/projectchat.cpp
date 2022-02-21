#include "projectchat.h"
#include "ui_projectchat.h"

ProjectChat::ProjectChat(QWidget *parent, int projId) :
    QWidget(parent),
    ui(new Ui::ProjectChat)
{
    ui->setupUi(this);
    this->projectId = projId;
    QString projectTitle = _projDataService.getProjectTitle(projectId);
    ui->BackToProjectBtn->setText("Back to "+projectTitle);
    ui->TitleLbl->setText(projectTitle);
    connect(ui->BackToProjectBtn, SIGNAL(released()), this, SLOT(returnToProject()));
    connect(ui->SendBtn, SIGNAL(released()), this, SLOT(sendMessageBtnPressed()));
    loadMessages();
    loadProjectUsers();
    setProgressBarValue();
}

void ProjectChat::returnToProject(){
    emit returnToProjectDashboard();
}

void ProjectChat::setProgressBarValue(){
     ui->projectProgress->setValue(_projDataService.calculateProjectProgress(_projDataService.getProjectTitle(projectId)));
     if(ui->projectProgress->value() == 100){
         if(usr.getUserRole() == roles.getRole("manager")){
             QPushButton *completeProjectBtn = new QPushButton("Mark project as complete");
             ui->widget->layout()->addWidget(completeProjectBtn);
         }
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
