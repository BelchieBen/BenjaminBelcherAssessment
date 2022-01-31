#ifndef MAINDASHBOARD_H
#define MAINDASHBOARD_H

#include <QDialog>
#include "taskdelegate.h"

namespace Ui {
class MainDashboard;
}

class MainDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit MainDashboard(QWidget *parent = nullptr);
    ~MainDashboard();

private:
    Ui::MainDashboard *ui;

private slots:
    void onAddTestTaskClicked();
};

#endif // MAINDASHBOARD_H
