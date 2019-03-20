#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "settings.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

signals:
    void settingsChanged();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_checkBoxMultipleInstances_stateChanged(int arg1);

    void on_checkBoxTrayIcon_stateChanged(int arg1);

    void on_checkBoxMinimizeToTray_stateChanged(int arg1);

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_pushButton_4_clicked();

    void saveSettings();

private:
    Ui::SettingsDialog *ui;
    Settings settings;

    Settings::MainWindowSettings mwSettings;
    Settings::EditorSettings eSettings;
};

#endif // SETTINGSDIALOG_H
