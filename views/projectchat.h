#ifndef PROJECTCHAT_H
#define PROJECTCHAT_H

#include <QWidget>
#include "services/projectdataservice.h"

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
private slots:
    void returnToProject();
signals:
    void returnToProjectDashboard();
};

#endif // PROJECTCHAT_H
