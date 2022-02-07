#ifndef PROJECTBTN_H
#define PROJECTBTN_H

#include <QSignalMapper>
#include <QWidget>
#include <QSqlQuery>
#include <QPushButton>
#include <QVBoxLayout>

class ProjectBtn: public QWidget
{
    Q_OBJECT
public:
    ProjectBtn(const QStringList &texts, QWidget *parent = nullptr);
signals:
    void clicked(const QString &text);
private:
    QSignalMapper *signalMapper;
};

#endif // PROJECTBTN_H
