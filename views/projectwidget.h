#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QWidget>
#include "globals/projectstates.h"

namespace Ui {
class ProjectWidget;
}

class ProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectWidget(QWidget *parent = nullptr,int id = 0, QString title = "", QString desc = "", QString status = "", QString manager = "");
    ~ProjectWidget();

private:
    Ui::ProjectWidget *ui;
    QString title;
    QString description;
    QString status;
    QString manager;
    int id;
    ProjectStates states;

private slots:
    void changeStatusColor();
    void onOpenClicked();

signals:
    void openProject(int id);
};

#endif // PROJECTWIDGET_H
