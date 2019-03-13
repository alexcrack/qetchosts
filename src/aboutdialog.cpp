#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QDebug>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());

    this->setWindowTitle(QString("About %1 - v%2").arg(APP_NAME).arg(APP_VERSION));

    ui->lblName->setText(APP_NAME);
    ui->lblVersion->setText(QString("version %1").arg(APP_VERSION));

    connect(ui->labelUrl, &QLabel::linkActivated, this, &AboutDialog::onLinkClicked);
    connect(ui->labelLibs, &QLabel::linkActivated, this, &AboutDialog::onLinkClicked);
    connect(ui->labelAuthors, &QLabel::linkActivated, this, &AboutDialog::onLinkClicked);

    ui->tabWidget->setCurrentIndex(0);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::onLinkClicked(QString link)
{
    QDesktopServices::openUrl(QUrl(link));
}
