#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "hostslistitem.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

    void setItem(HostsListItem *item);

public Q_SLOTS:
    virtual void accept();

private:
    Ui::AddDialog *ui;

    HostsListItem *item;
};

#endif // ADDDIALOG_H
