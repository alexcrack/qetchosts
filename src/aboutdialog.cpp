#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());

    this->setWindowTitle(QString("%1 - v%2").arg(APP_NAME).arg(APP_VERSION));

    ui->lblName->setText(APP_NAME);
    ui->lblVersion->setText(QString("version %1").arg(APP_VERSION));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
