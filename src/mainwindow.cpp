#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "consts.h"
#include "aboutdialog.h"
#include "adddialog.h"
#include "settingsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mwSettings = settings.getWindowSettings();

    setupWindow();
    setupTrayIcon();
    setupTemplateListActions();
    setupEditor();
    setupHosts();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete hostsMapper;
    delete trayIcon;
    delete trayIconMenu;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (mwSettings.minimizeToTrayIcon && trayIcon->isVisible()) {
        hide();
        event->ignore();
    } else {
        saveWindow();

        event->accept();
    }
}

void MainWindow::setupWindow()
{
    setWindowTitle(QString("%1 - v%2").arg(APP_NAME).arg(APP_VERSION));

    resize(mwSettings.size);
    move(mwSettings.pos);
    ui->splitter->restoreState(mwSettings.splitter);
}

void MainWindow::setupTrayIcon()
{
    trayIcon = new QSystemTrayIcon(QIcon(":/toolbar/icons/icon.svg"));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(ui->actionTray_Untray);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(ui->actionExit);

    trayIcon->setContextMenu(trayIconMenu);

    if (mwSettings.showTrayIcon) {
        trayIcon->show();
    }

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::on_iconActivated);
}

void MainWindow::setupTemplateListActions()
{
    ui->hostGroupsListView->addAction(ui->actionAdd_Template);
    ui->hostGroupsListView->addAction(ui->actionMove_Up);
    ui->hostGroupsListView->addAction(ui->actionMove_Down);
    ui->hostGroupsListView->addAction(ui->actionRemove_Template);
    ui->hostGroupsListView->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::saveWindow()
{
    mwSettings.size = this->size();
    mwSettings.pos = this->pos();
    mwSettings.splitter = ui->splitter->saveState();

    settings.setWindowSettings(mwSettings);
}

void MainWindow::on_iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        show();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

void MainWindow::setupEditor()
{

}

void MainWindow::setupHosts()
{
    model = new HostsListModel(this);
    hostsMapper = new QDataWidgetMapper(this);

    ui->hostGroupsListView->setModel(model);

    hostsMapper->setModel(model);
    hostsMapper->addMapping(ui->textEdit, HostsListItem::Field::Hosts, "plainText");
    hostsMapper->toFirst();

    connect(ui->hostGroupsListView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::hostsSelectionChanged);

//    ui->hostGroupsListView->selectionModel()->select();
}

void MainWindow::hostsSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndex index = ui->hostGroupsListView->selectionModel()->currentIndex();
    hostsMapper->setCurrentModelIndex(index);
}

void MainWindow::on_action_Save_triggered()
{
    model->save();
}

void MainWindow::on_actionExit_triggered()
{
    trayIcon->hide();
    close();
}

void MainWindow::on_action_About_triggered()
{
    AboutDialog *about = new AboutDialog(this);

    about->show();
}

void MainWindow::on_actionAdd_Template_triggered()
{
    AddDialog *addDialog = new AddDialog(this);
    addDialog->setWindowTitle(ui->actionAdd_Template->toolTip());

    HostsListItem *newItem = new HostsListItem();
    addDialog->setItem(newItem);

    if (addDialog->exec() == QDialog::Accepted) {
        QModelIndex index = model->addTemplateItem(newItem);

        ui->hostGroupsListView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::SelectCurrent);
    }
}

void MainWindow::on_actionMove_Up_triggered()
{
    QModelIndex index = ui->hostGroupsListView->selectionModel()->currentIndex();

    QModelIndex newIndex = model->moveTemplateItem(index, true);

    ui->hostGroupsListView->selectionModel()->setCurrentIndex(newIndex, QItemSelectionModel::SelectCurrent);
}

void MainWindow::on_actionMove_Down_triggered()
{
    QModelIndex index = ui->hostGroupsListView->selectionModel()->currentIndex();

    QModelIndex newIndex = model->moveTemplateItem(index, false);

    ui->hostGroupsListView->selectionModel()->setCurrentIndex(newIndex, QItemSelectionModel::SelectCurrent);
}

void MainWindow::on_actionRemove_Template_triggered()
{
    QModelIndex index = ui->hostGroupsListView->selectionModel()->currentIndex();

    model->removeTemplateItem(index);
}

void MainWindow::on_actionTray_Untray_triggered()
{
    if (isVisible()) {
        hide();
    } else {
        show();
    }
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog *settingsDialog = new SettingsDialog(this);

    connect(settingsDialog, &SettingsDialog::settingsChanged, this, [this]() {
        mwSettings = settings.getWindowSettings();

        if (mwSettings.showTrayIcon) {
            trayIcon->show();
        } else {
            trayIcon->hide();
        }
    });

    connect(settingsDialog, &SettingsDialog::settingsChanged, ui->textEdit, &CodeEditor::setEditor);

    settingsDialog->show();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_action_Help_triggered()
{

}
