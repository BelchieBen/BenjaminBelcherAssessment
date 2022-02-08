#include "otherprojectsdialog.h"
#include "ui_otherprojectsdialog.h"

OtherProjectsDialog::OtherProjectsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OtherProjectsDialog)
{
    ui->setupUi(this);
}

OtherProjectsDialog::~OtherProjectsDialog()
{
    delete ui;
}
