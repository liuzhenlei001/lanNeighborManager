#include "mainwnd.h"
#include "ui_mainwnd.h"
#include "localhost.h"
#include <QStyleFactory>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QTreeWidgetItem>

MainWnd::MainWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWnd),
    m_translator(NULL),
    m_timer(NULL),
    m_neighborPagesMap()
{
    ui->setupUi(this);
    ui->localEthTreeWidget->setStyle(QStyleFactory::create("windows"));

    connect(ui->langRadioGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(on_langRadioGroupToggled(QAbstractButton*,bool)));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    m_timer->start(1000);

    refreshLocalHost();
}

MainWnd::~MainWnd()
{
    delete ui;
}

void MainWnd::setTranslator(QTranslator *translator)
{
    this->m_translator = translator;
}

void MainWnd::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        this->setWindowTitle(tr("LanHostManager"));
//        ui->btnIdleSelected->setText(tr("Idle Selected"));
//        ui->btnBusySelected->setText(tr("Busy Selected"));
        ui->btnLocalEthRefresh->setText(tr("Refresh"));
    }
    else
    {
        QWidget::changeEvent(event);
    }
}

void MainWnd::refreshLocalHost()
{
    QSet<QString> latest_local_ips;
    QMap<QString, QString> local_interfaces = LocalHost::getAllInterfaces();
    for(QMap<QString, QString>::const_iterator iter = local_interfaces.constBegin();
        iter != local_interfaces.constEnd();
        ++iter)
    {
        QString if_name = iter.key();
        QString if_ip = iter.value();
        latest_local_ips.insert(if_ip);

        QTreeWidgetItem *item_name = new QTreeWidgetItem(QStringList()<<if_name);
        item_name->setData(0, HiliRole, QVariant(int(HILI_NAME)));
        ui->localEthTreeWidget->addTopLevelItem(item_name);

        QTreeWidgetItem *item_ip = new QTreeWidgetItem(QStringList()<<if_ip);
        item_ip->setData(0, HiliRole, QVariant(int(HILI_IPV4)));
        item_name->addChild(item_ip);
    }

    QSet<QString> last_local_ips = m_neighborPagesMap.keys().toSet();
    QSet<QString> wait_to_delete_local_ips = last_local_ips - latest_local_ips;
    for(QSet<QString>::const_iterator iter = wait_to_delete_local_ips.constBegin();
        iter != wait_to_delete_local_ips.constEnd();
        ++iter)
    {
        NeighborHostStackPage *page = m_neighborPagesMap.take(*iter);
        ui->neighborStackWidget->removeWidget(page);
        delete page;
        page = NULL;
    }

    QSet<QString> wait_to_add_local_ips = latest_local_ips - last_local_ips;
    for(QSet<QString>::const_iterator iter = wait_to_add_local_ips.constBegin();
        iter != wait_to_add_local_ips.constEnd();
        ++iter)
    {
        NeighborHostStackPage *page = new NeighborHostStackPage(*iter, this);
        m_neighborPagesMap.insert(*iter, page);
        ui->neighborStackWidget->addWidget(page);
    }
    ui->neighborStackWidget->setCurrentIndex(0);
}

void MainWnd::refreshNeighborHosts(QString local_host_ip)
{
    ;
}

void MainWnd::on_btnLocalEthRefresh_clicked()
{
    ui->localEthTreeWidget->clear();
    refreshLocalHost();
}

void MainWnd::on_localEthTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(item == NULL || column < 0)
        return;

    HostInfoLayerIndex hili = (HostInfoLayerIndex)(item->data(0, HiliRole).toInt());
    if(hili != HILI_IPV4)
        return;

    ui->neighborStackWidget->setCurrentWidget(m_neighborPagesMap[item->text(0)]);
}

void MainWnd::on_langRadioGroupToggled(QAbstractButton *button, bool checked)
{
    if(button == ui->radioEn)
    {
        m_translator->load(":/languages/language_en.qm");
    }
    else if(button == ui->radioCn)
    {
        m_translator->load(":/languages/language_zh.qm");
    }
    else
    {
        ;
    }
}

void MainWnd::on_timeout()
{
    ;
}
