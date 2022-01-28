#ifndef MAINDASHBOARD_H
#define MAINDASHBOARD_H

#include <QDialog>

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
};

#endif // MAINDASHBOARD_H
