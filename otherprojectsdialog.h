#ifndef OTHERPROJECTSDIALOG_H
#define OTHERPROJECTSDIALOG_H

#include <QDialog>

namespace Ui {
class OtherProjectsDialog;
}

class OtherProjectsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OtherProjectsDialog(QWidget *parent = nullptr);
    ~OtherProjectsDialog();

private:
    Ui::OtherProjectsDialog *ui;
};

#endif // OTHERPROJECTSDIALOG_H
