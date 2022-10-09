#include "neighborhostwidget.h"
#include "ui_neighborhostwidget.h"

NeighborHostWidget::NeighborHostWidget(QString neighbor_ip, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NeighborHostWidget)
{
    ui->setupUi(this);

    ui->labelIp->setText(neighbor_ip);
}

NeighborHostWidget::~NeighborHostWidget()
{
    delete ui;
}

void NeighborHostWidget::setUserVisible(bool isVisible)
{
//    ui->labelUserStatic->setVisible(isVisible);
    ui->labelUser->setVisible(isVisible);
}

void NeighborHostWidget::setUser(QString user)
{
    ui->labelUser->setText(user);
}

void NeighborHostWidget::clearUser()
{
    ui->labelUser->setText("---");
}

bool NeighborHostWidget::hasUser()
{
    return ui->labelUser->text().compare("---")!=0;
}

void NeighborHostWidget::setStateVisible(bool isVisible)
{
//    ui->labelStateStatic->setVisible(isVisible);
    ui->labelState->setVisible(isVisible);
}

void NeighborHostWidget::setState(bool isUp)
{
    if(isUp)
    {
        ;
    }
    else
    {
        ;
    }
}

QString NeighborHostWidget::getIp()
{
    return ui->labelIp->text();
}

void NeighborHostWidget::reset()
{
//    ui->labelIp->setStyleSheet("");
}

void NeighborHostWidget::refresh()
{
    QHostInfo::lookupHost(ui->labelIp->text(), this, SLOT(on_lookup_return(QHostInfo)));
}

void NeighborHostWidget::on_lookup_return(const QHostInfo &host)
{
    if(host.addresses()[0].toString().compare(host.hostName()) != 0)
//    {
////        ui->labelIp->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(255, 85, 0);");
//    }
//    else
//    {
//        if(host.error() != QHostInfo::NoError)
        {
            ui->labelState->setStyleSheet("background-color: rgb(42, 126, 0);");
        }
        else
        {
            if(this->hasUser())
            {
                ui->labelState->setStyleSheet("background-color: rgb(208, 0, 0);");
            }
            else
            {
                ui->labelState->setStyleSheet("background-color: rgb(156, 156, 156);");
            }
        }
//    }
//    if((host.error() != QHostInfo::NoError))
//    {
//        ui->labelIp->setStyleSheet("");
//        if();
//    }
//    else
//    {

//    }
}

//void NeighborHostWidget::on_neighbor_found(QString neighbor_ip)
//{
//    if(ui->labelIp->text().compare(neighbor_ip) != 0)
//        return;

//    ui->labelIp->setStyleSheet();
//}
