#include "quickloginpage.h"
#include "ui_quickloginpage.h"

QuickLoginPage::QuickLoginPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuickLoginPage)
{
    ui->setupUi(this);
    ui->PinEntry->setValidator(new QIntValidator(0, 9999, this));
    ui->TitleLbl->setText(usr.GetCurrentUserEmail());
    connect(ui->LoginBtn, SIGNAL(released()), this, SLOT(onLoginClicked()));
}

void QuickLoginPage::onLoginClicked(){
    QString pin = ui->PinEntry->text();
    if(_auth.quickLogin(pin)){
        this->hide();
        loginLandingPage.setModal(true);
        loginLandingPage.exec();
    }
    else{
        _messageBox.critical(0, "Error", "Incorrect PIN");
    }
}

QuickLoginPage::~QuickLoginPage()
{
    delete ui;
}
