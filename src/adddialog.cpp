#include "adddialog.h"
#include "ui_adddialog.h"

#include <QDebug>

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::setItem(HostsListItem *item)
{
    this->item = item;
}

void AddDialog::accept()
{
    item->name = ui->editName->text();
    item->description = ui->editDescription->toPlainText();

    QDialog::accept();
}
