#include "neighboruserlabel.h"
#include "ui_neighboruserlabel.h"
#include <QPoint>

NeighborUserLabel::NeighborUserLabel(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::NeighborUserLabel)
{
    ui->setupUi(this);

//    QAction *user_set_action = m_contextMenu.addAction("Set User");
//    QAction *user_clear_action = m_contextMenu.addAction("Clear User");
}

NeighborUserLabel::~NeighborUserLabel()
{
    delete ui;
}

//void NeighborUserLabel::contextMenuEvent(QContextMenuEvent *event)
//{
//    ;
//}
