#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDataWidgetMapper>
#include <QItemSelection>
#include <QSystemTrayIcon>
#include <QMenu>

#include "settings.h"
#include "hostslistmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private slots:
    void on_action_Save_triggered();

    void on_actionExit_triggered();

    void on_action_About_triggered();

    void on_actionAdd_Template_triggered();

    void on_actionMove_Up_triggered();

    void on_actionMove_Down_triggered();

    void on_actionRemove_Template_triggered();

    void on_iconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_actionTray_Untray_triggered();

    void on_actionSettings_triggered();

    void on_actionAbout_Qt_triggered();

    void on_action_Help_triggered();

private:
    Ui::MainWindow *ui;

    Settings settings;
    Settings::MainWindowSettings mwSettings;

    HostsListModel *model;
    QDataWidgetMapper *hostsMapper;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    void setupWindow();
    void setupTrayIcon();
    void setupTemplateListActions();
    void saveWindow();
    void setupEditor();
    void setupHosts();
    void hostsSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // MAINWINDOW_H
