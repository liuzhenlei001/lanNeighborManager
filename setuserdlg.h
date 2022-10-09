#ifndef SETUSERDLG_H
#define SETUSERDLG_H

#include <QDialog>
#include <QEvent>

namespace Ui {
class SetUserDlg;
}

class SetUserDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SetUserDlg(QWidget *parent = 0);
    ~SetUserDlg();

    QString getUser();

protected:
    virtual void changeEvent(QEvent *event);

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::SetUserDlg *ui;
};

#endif // SETUSERDLG_H
