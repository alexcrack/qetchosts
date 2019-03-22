#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QDebug>
#include <QColor>

#include "settings.h"
#include "settings/colorbutton.h"

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

    void on_spinBoxFontSize_valueChanged(int arg1);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void foregroundChanged(QColor color);

    void backgroundChanged(QColor color);

    void on_checkBoxBold_stateChanged(int arg1);

    void on_checkBoxItalic_stateChanged(int arg1);

private:
    Ui::SettingsDialog *ui;
    Settings settings;

    Settings::MainWindowSettings mwSettings;
    Settings::EditorSettings eSettings;
};

#endif // SETTINGSDIALOG_H
