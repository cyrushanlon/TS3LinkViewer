#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :QWidget(parent), ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::showEvent(QShowEvent *)
{
    if (Settings != NULL)
    {
        ui->AutoCheckBox->setChecked(Settings->AutoLoad);
        ui->LinkCountDial->setValue(Settings->HistoryLength);
        ui->DialDisplay->setText(QString::number(Settings->HistoryLength));
        //Hotkeys
        ui->OpenHotkeyEdit->setText(Settings->OpenHotkey);
        ui->CloseHotkeyEdit->setText(Settings->CloseHotkey);
        ui->AutoHotkeyEdit->setText(Settings->AutoHotkey);
    }
}

void SettingsDialog::on_DiscardButton_clicked()
{
    this->close();
}

void SettingsDialog::on_AcceptButton_clicked()
{
    Settings->AutoLoad = ui->AutoCheckBox->checkState();
    Settings->HistoryLength = ui->DialDisplay->text().toInt();
    //Hotkeys
    Settings->OpenHotkey = ui->OpenHotkeyEdit->toPlainText();
    Settings->CloseHotkey = ui->CloseHotkeyEdit->toPlainText();
    Settings->AutoHotkey = ui->AutoHotkeyEdit->toPlainText();

    Settings->SaveFile();
    this->hide();
}

void SettingsDialog::on_LinkCountDial_sliderMoved(int position)
{
    ui->DialDisplay->setText(QString::number(position));
}

void SettingsDialog::on_AutoCheckBox_stateChanged(int)
{
    if (ui->AutoCheckBox->checkState())
    {
        ui->LinkCountDial->setEnabled(false);
        ui->CloseHotkeyEdit->setEnabled(false);
    }
    else
    {
        ui->LinkCountDial->setEnabled(true);
        ui->CloseHotkeyEdit->setEnabled(true);
    }
}
