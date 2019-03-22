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
    ui->spinBoxFontSize->setValue(eSettings.font.pointSize());

    for (auto r : eSettings.highlights) {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);

        item->setText(r.name);
        item->setForeground(r.format.foreground());
        item->setBackground(r.format.background());

        QFont font = item->font();
        font.setBold(r.format.fontWeight() == QFont::Bold);
        font.setItalic(r.format.fontItalic());
        item->setFont(font);
    }

    ui->tabWidget->setCurrentIndex(0);
    ui->listWidget->setCurrentRow(0);

    connect(ui->btnForeground, &ColorButton::colorChanged, this, &SettingsDialog::foregroundChanged);
    connect(ui->btnBackground, &ColorButton::colorChanged, this, &SettingsDialog::backgroundChanged);
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

    ui->listWidget->setFont(eSettings.font);
}

void SettingsDialog::on_pushButton_4_clicked()
{
    saveSettings();
}

void SettingsDialog::saveSettings()
{
    settings.setWindowSettings(mwSettings);

    for (int i = 0; i < eSettings.highlights.count(); i++) {
        auto r = eSettings.highlights.at(i);
        auto *item = ui->listWidget->item(i);

        QTextCharFormat format;
        format.setFontWeight(item->font().weight());
        format.setFontItalic(item->font().italic());
        format.setForeground(item->foreground());
        format.setBackground(item->background());

        r.format = format;

        eSettings.highlights.replace(i, r);
    }

    settings.setEditorSettings(eSettings);

    emit settingsChanged();
}

void SettingsDialog::on_spinBoxFontSize_valueChanged(int arg1)
{
    eSettings.font.setPointSize(arg1);

    ui->fontComboBox->setCurrentFont(eSettings.font);
    ui->listWidget->setFont(eSettings.font);
}

void SettingsDialog::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->btnForeground->setColor(current->foreground().color());
    ui->btnBackground->setColor(current->backgroundColor());

    QFont font = ui->listWidget->currentItem()->font();

    ui->checkBoxBold->setChecked(font.bold());
    ui->checkBoxItalic->setChecked(font.italic());
}

void SettingsDialog::foregroundChanged(QColor color)
{
    ui->listWidget->currentItem()->setForeground(color);
}

void SettingsDialog::backgroundChanged(QColor color)
{
    ui->listWidget->currentItem()->setBackground(color);
}

void SettingsDialog::on_checkBoxBold_stateChanged(int arg1)
{
    QFont font = ui->listWidget->currentItem()->font();
    font.setBold(arg1 == Qt::Checked);

    ui->listWidget->currentItem()->setFont(font);
}

void SettingsDialog::on_checkBoxItalic_stateChanged(int arg1)
{
    QFont font = ui->listWidget->currentItem()->font();
    font.setItalic(arg1 == Qt::Checked);

    ui->listWidget->currentItem()->setFont(font);
}
