#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    mwSettings = settings.getWindowSettings();

    ui->checkBoxMultipleInstances->setChecked(mwSettings.multipleInstances);
    ui->checkBoxTrayIcon->setChecked(mwSettings.showTrayIcon);
    ui->checkBoxMinimizeToTray->setChecked(mwSettings.minimizeToTrayIcon);

    eSettings = settings.getEditorSettings();

    ui->fontComboBox->setCurrentFont(eSettings.font);
    ui->spinBoxFontSize->setValue(eSettings.fontSize);

    ui->tabWidget->setCurrentIndex(0);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_pushButton_3_clicked()
{
    close();
}

void SettingsDialog::on_pushButton_2_clicked()
{
    saveSettings();

    accept();
}

void SettingsDialog::on_checkBoxMultipleInstances_stateChanged(int arg1)
{
    mwSettings.multipleInstances = static_cast<bool>(arg1);
}

void SettingsDialog::on_checkBoxTrayIcon_stateChanged(int arg1)
{
    mwSettings.showTrayIcon = static_cast<bool>(arg1);

    if (!mwSettings.showTrayIcon) {
        on_checkBoxMinimizeToTray_stateChanged(0);
        ui->checkBoxMinimizeToTray->setEnabled(false);
    } else {
        ui->checkBoxMinimizeToTray->setEnabled(true);
    }
}

void SettingsDialog::on_checkBoxMinimizeToTray_stateChanged(int arg1)
{
    mwSettings.minimizeToTrayIcon = static_cast<bool>(arg1);
}

void SettingsDialog::on_fontComboBox_currentFontChanged(const QFont &f)
{
    eSettings.font = f;
}

void SettingsDialog::on_pushButton_4_clicked()
{
    saveSettings();
}

void SettingsDialog::saveSettings()
{
    settings.setWindowSettings(mwSettings);
    settings.setEditorSettings(eSettings);

    emit settingsChanged();
}
