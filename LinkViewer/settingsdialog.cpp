#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "widget.h"

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
        ui->AutoCheckBox->setChecked(Settings->GetBool("AutoLoad") == 1);
        ui->LinkCountDial->setValue(Settings->GetInt("LinkHistory"));
        ui->DialDisplay->setText(Settings->Get("LinkHistory"));
        //Hotkeys
        ui->OpenHotkeyEdit->setText(Settings->Get("HotkeyOpen"));
        ui->CloseHotkeyEdit->setText(Settings->Get("HotkeyClose"));
        ui->AutoHotkeyEdit->setText(Settings->Get("HotkeyAuto"));
    }
}

void SettingsDialog::on_DiscardButton_clicked()
{
    this->close();
}

void SettingsDialog::on_AcceptButton_clicked()
{
    Settings->Set("AutoMode",ui->AutoCheckBox->checkState());
    Settings->Set("LinkHistory",ui->DialDisplay->text().toInt());
    //Hotkeys
    Settings->Set("HotkeyOpen",ui->OpenHotkeyEdit->toPlainText());
    Settings->Set("HotkeyClose",ui->CloseHotkeyEdit->toPlainText());
    Settings->Set("HotkeyAuto",ui->AutoHotkeyEdit->toPlainText());

    Settings->SaveFile();

    this->hide();

    qApp->exit(1337);
}

void SettingsDialog::on_LinkCountDial_sliderMoved(int position)
{
    ui->DialDisplay->setText(QString::number(position));
}
