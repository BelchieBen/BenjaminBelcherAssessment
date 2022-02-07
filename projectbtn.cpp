#include "projectbtn.h"

ProjectBtn::ProjectBtn(const QStringList &texts, QWidget *parent)
    : QWidget(parent)
{
    signalMapper = new QSignalMapper(this);
    QSqlQuery q;
    q.prepare("SELECT * FROM projects");
    QVBoxLayout *stackLayout = new QVBoxLayout;
    if(q.exec()){
        QPushButton *projectBtn;
        int count = 0;
        while(q.next()){
            projectBtn = new QPushButton(q.value(1).toString());
            connect(projectBtn, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(projectBtn, texts[count]);
            stackLayout->addWidget(projectBtn);
            count++;
        }
    }

    connect(signalMapper, &QSignalMapper::mappedString, this, &ProjectBtn::clicked);
    setLayout(stackLayout);
}
