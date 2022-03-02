#ifndef PROJECTCHAT_H
#define PROJECTCHAT_H

#include <QWidget>
#include "services/projectdataservice.h"
#include "models/user.h"
#include "models/projectmessage.h"
#include "delegates/messagedelegate.h"
#include "globals/userroles.h"

namespace Ui {
class ProjectChat;
}

class ProjectChat : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectChat(QWidget *parent = nullptr, int projectId = 0);
    ~ProjectChat();

private:
    Ui::ProjectChat *ui;
    int projectId;
    ProjectDataService _projDataService;
    user usr;
    UserRoles roles;
    ProjectStates states;
    EmailServerDetails details;
    QPushButton *completeProjectBtn;

private slots:
    void returnToProject();
    void sendMessageBtnPressed();
    void loadMessages();
    void loadProjectUsers();
    void setProgressBarValue();
    void markProjectAsComplete();

signals:
    void returnToProjectDashboard();
    void projectComplete();
};

#endif // PROJECTCHAT_H
