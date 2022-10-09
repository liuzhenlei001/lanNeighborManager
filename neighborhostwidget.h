#ifndef NEIGHBORHOSTWIDGET_H
#define NEIGHBORHOSTWIDGET_H

#include <QWidget>
#include <QHostInfo>

namespace Ui {
class NeighborHostWidget;
}

class NeighborHostWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NeighborHostWidget(QString neighbor_ip, QWidget *parent = 0);
    ~NeighborHostWidget();

    void setUserVisible(bool isVisible);
    void setUser(QString user);
    void clearUser();
    bool hasUser();

    void setStateVisible(bool isVisible);
    void setState(bool isUp);

    QString getIp();
    void reset();
    void refresh();

protected:

private:

private slots:
    void on_lookup_return(const QHostInfo &host);

signals:

private:
    Ui::NeighborHostWidget *ui;
};

#endif // NEIGHBORHOSTWIDGET_H
