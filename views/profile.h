#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include "models/user.h"

namespace Ui {
class Profile;
}

class Profile : public QWidget
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();

private:
    Ui::Profile *ui;
    user usr;

private slots:
    void returnToMainDashboard();
    void populateTreeWidget();
signals:
    void returnToDashboard();
};

#endif // PROFILE_H
