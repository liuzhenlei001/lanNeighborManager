#ifndef NEIGHBORUSERLABEL_H
#define NEIGHBORUSERLABEL_H

#include <QWidget>
#include <QLabel>
#include <QContextMenuEvent>
//#include <QMenu>
//#include <QAction>

namespace Ui {
class NeighborUserLabel;
}

class NeighborUserLabel : public QLabel
{
    Q_OBJECT

public:
    explicit NeighborUserLabel(QWidget *parent = 0);
    ~NeighborUserLabel();

protected:
//    virtual void contextMenuEvent(QContextMenuEvent *event);

private:
    Ui::NeighborUserLabel *ui;
//    QMenu m_contextMenu;
};

#endif // NEIGHBORUSERLABEL_H
