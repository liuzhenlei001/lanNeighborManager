#include "neighborhoststackpage.h"
#include "ui_neighborhoststackpage.h"
#include "neighborhostwidget.h"
#include "setuserdlg.h"
#include <QLabel>
#include <QAction>
#include <QTableWidgetSelectionRange>

NeighborHostStackPage::NeighborHostStackPage(QString local_ip, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NeighborHostStackPage),
    m_local_ip(local_ip)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(IP_PER_ROW);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    for(int col = 0; col < IP_PER_ROW; ++col)
    {
        ui->tableWidget->setColumnWidth(col, 200);
    }

    init_ui();

    QAction *user_set_action = m_contextMenu.addAction(tr("Set User"));
    connect(user_set_action, SIGNAL(triggered(bool)), this, SLOT(on_set_user_action_triggered(bool)));
    QAction *user_clear_action = m_contextMenu.addAction(tr("Clear User"));
    connect(user_clear_action, SIGNAL(triggered(bool)), this, SLOT(on_clear_user_action_triggered(bool)));
}

NeighborHostStackPage::~NeighborHostStackPage()
{
    delete ui;
}

//void NeighborHostStackPage::resizeEvent(QResizeEvent *event)
//{
//    int col_width = this->width() / IP_PER_ROW;
//    for(int i = 0; i < IP_PER_ROW; ++i)
//    {
//        ui->tableWidget->setColumnWidth(i, col_width-5);
//    }
//}

void NeighborHostStackPage::contextMenuEvent(QContextMenuEvent *event)
{
    QList<QTableWidgetSelectionRange> sel_range = ui->tableWidget->selectedRanges();
    if(sel_range.size() != 1)
    {
        return;
    }
    if(sel_range.at(0).rowCount() > 1 || sel_range.at(0).columnCount() > 1)
    {
        return;
    }

    QPoint global_cursor_pos = mapToGlobal(this->pos()+event->pos());
    m_contextMenu.exec(global_cursor_pos);
}

void NeighborHostStackPage::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->btnRefresh->setText(tr("Refresh"));
        ui->btnClearUser->setText(tr("Clear User"));
        ui->btnSetUser->setText(tr("Set User"));

        m_contextMenu.actions()[0]->setText(tr("Set User"));
        m_contextMenu.actions()[1]->setText(tr("Clear User"));
    }
    else
    {
        QWidget::changeEvent(event);
    }
}

void NeighborHostStackPage::reset()
{
    for(int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        for(int col = 0; col < ui->tableWidget->columnCount(); ++col)
        {
            NeighborHostWidget *neighbor_host = dynamic_cast<NeighborHostWidget *>(ui->tableWidget->cellWidget(row, col));
            if(neighbor_host)
            {
                neighbor_host->reset();
            }
        }
    }
}

void NeighborHostStackPage::init_ui()
{
    ui->btnClearUser->setEnabled(false);
    ui->btnSetUser->setEnabled(false);

    QStringList ip_parts = m_local_ip.split('.');
    if(ip_parts.size() != 4)
        return;

    QString ip_prefix = m_local_ip.left(m_local_ip.lastIndexOf('.')+1);
    for(int i = 1; i <= 255; ++i)
    {
        QString ip = QString("%1%2").arg(ip_prefix).arg(i);
        int row = (i-1)/IP_PER_ROW;
        int col = (i-1)%IP_PER_ROW;
        if(ui->tableWidget->rowCount() < row+1)
        {
            ui->tableWidget->insertRow(row);
        }

        NeighborHostWidget *neighbor_host = new NeighborHostWidget(ip, this);
        ui->tableWidget->setCellWidget(row, col, neighbor_host);
        if(m_local_ip.compare(ip) == 0)
        {
            neighbor_host->setStyleSheet("background-color: rgb(175, 175, 175);color: rgb(0, 0, 0);font: 20pt \"Agency FB\";");
            neighbor_host->setUserVisible(false);
            neighbor_host->setStateVisible(false);
        }
    }
}

void NeighborHostStackPage::on_btnRefresh_clicked()
{
    reset();

    for(int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        for(int col = 0; col < ui->tableWidget->columnCount(); ++col)
        {
            QWidget *cell_widget = ui->tableWidget->cellWidget(row, col);
            if(cell_widget == NULL)
                continue;

            NeighborHostWidget *neighbor_host = dynamic_cast<NeighborHostWidget *>(cell_widget);
            if(neighbor_host->getIp().compare(m_local_ip) == 0)
            {
//                neighbor_host->refresh();
                neighbor_host->setStyleSheet("background-color: rgb(175, 175, 175);color: rgb(0, 0, 0);font: 20pt \"Agency FB\";");
            }
            else
            {
                neighbor_host->refresh();
            }
        }
    }
}

void NeighborHostStackPage::on_clear_user_action_triggered(bool checked)
{
    (void)checked;

    NeighborHostWidget *neighbor_host = dynamic_cast<NeighborHostWidget *>(ui->tableWidget->cellWidget(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn()));
    if(neighbor_host == NULL)
    {
        return;
    }
    neighbor_host->clearUser();
}

void NeighborHostStackPage::on_set_user_action_triggered(bool checked)
{
    (void)checked;

    NeighborHostWidget *neighbor_host = dynamic_cast<NeighborHostWidget *>(ui->tableWidget->cellWidget(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn()));
    if(neighbor_host == NULL)
    {
        return;
    }

    SetUserDlg dlg;
    int ret = dlg.exec();
    if(ret == QDialog::Accepted)
    {
        neighbor_host->setUser(dlg.getUser());
    }
    else
    {
        ;
    }
}

void NeighborHostStackPage::on_btnSetUser_clicked()
{
    on_set_user_action_triggered(true);
}

void NeighborHostStackPage::on_btnClearUser_clicked()
{
    on_clear_user_action_triggered(true);
}

void NeighborHostStackPage::on_tableWidget_cellClicked(int row, int column)
{
    (void)row;
    (void)column;

    QList<QTableWidgetSelectionRange> sel_ranges = ui->tableWidget->selectedRanges();
    if(sel_ranges.size() != 1)
    {
        ui->btnSetUser->setEnabled(false);
        ui->btnClearUser->setEnabled(false);
    }
    else
    {
        if(sel_ranges.at(0).columnCount() > 1 || sel_ranges.at(0).rowCount() > 1)
        {
            ui->btnSetUser->setEnabled(false);
            ui->btnClearUser->setEnabled(false);
        }
        else
        {
            ui->btnSetUser->setEnabled(true);
            ui->btnClearUser->setEnabled(true);
        }
    }
}
