#ifndef NEIGHBORHOSTSTACKPAGE_H
#define NEIGHBORHOSTSTACKPAGE_H

#include <QWidget>
#include <QResizeEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QEvent>

#define IP_PER_ROW (10)

namespace Ui {
class NeighborHostStackPage;
}

class NeighborHostStackPage : public QWidget
{
    Q_OBJECT

public:
    explicit NeighborHostStackPage(QString local_ip, QWidget *parent = 0);
    ~NeighborHostStackPage();

    void reset();

protected:
//    virtual void resizeEvent(QResizeEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);
    virtual void changeEvent(QEvent *event);

private slots:
    void on_btnRefresh_clicked();

    void on_clear_user_action_triggered(bool checked);
    void on_set_user_action_triggered(bool checked);

    void on_btnSetUser_clicked();

    void on_btnClearUser_clicked();

    void on_tableWidget_cellClicked(int row, int column);

private:
    void init_ui();

private:
    Ui::NeighborHostStackPage *ui;
    QString m_local_ip;
    QMenu m_contextMenu;
};

#endif // NEIGHBORHOSTSTACKPAGE_H
