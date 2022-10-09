#include "setuserdlg.h"
#include "ui_setuserdlg.h"

SetUserDlg::SetUserDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetUserDlg)
{
    ui->setupUi(this);
}

SetUserDlg::~SetUserDlg()
{
    delete ui;
}

QString SetUserDlg::getUser()
{
    return ui->textUser->text();
}

void SetUserDlg::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        this->setWindowTitle(tr("UserSettingDlg"));
        ui->labelUser->setText(tr("User:"));
        ui->textUser->setPlaceholderText(tr("Please type in user name..."));
        ui->btnOK->setText(tr("OK"));
        ui->btnCancel->setText(tr("Cancel"));
    }
    else
    {
        QDialog::changeEvent(event);
    }
}

void SetUserDlg::on_btnOK_clicked()
{
    this->accept();
}

void SetUserDlg::on_btnCancel_clicked()
{
    this->reject();
}
