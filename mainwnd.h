#ifndef MAINWND_H
#define MAINWND_H

#include "neighborhoststackpage.h"

#include <QWidget>
#include <Qt>
#include <QMap>
#include <QTreeWidgetItem>
#include <QAbstractButton>
#include <QTranslator>
#include <QEvent>
#include <QTimer>

#define HiliRole (Qt::UserRole+1)

typedef enum _HOST_INFO_LAYER_INDEX_ {
    HILI_NAME = 0,
    HILI_IPV4 = 1,
    HILI_INVALID
}HostInfoLayerIndex;

namespace Ui {
class MainWnd;
}

class MainWnd : public QWidget
{
    Q_OBJECT

public:
    explicit MainWnd(QWidget *parent = 0);
    ~MainWnd();

    void setTranslator(QTranslator *translator);

protected:
    virtual void changeEvent(QEvent *event);

private slots:
    void on_btnLocalEthRefresh_clicked();
    void on_localEthTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_langRadioGroupToggled(QAbstractButton *button, bool checked);

    void on_timeout();

private:
    void refreshLocalHost();
    void refreshNeighborHosts(QString local_host_ip);

private:
    Ui::MainWnd *ui;
    QTranslator *m_translator;
    QTimer *m_timer;

    QMap<QString, NeighborHostStackPage*> m_neighborPagesMap;
};

#endif // MAINWND_H
