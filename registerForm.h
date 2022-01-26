#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QDialog>

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = nullptr);
    ~RegisterForm();

private:
    Ui::RegisterForm *ui;

private slots:
    void onAlreadyGotAccountPressed();
    void onRegisterPressed();
};

#endif // REGISTERFORM_H
