#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "widget.h"

SettingsDialog::SettingsDialog(QWidget *parent) :QWidget(parent), ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::showEvent(QShowEvent *)
{    
    if (Settings != NULL)
    {
        ui->RemPosCheckBox->setChecked(Settings->GetBool("RememberPos"));
        ui->HideCheckBox->setChecked(Settings->GetBool("HideWin"));
        ui->HideBarCheckBox->setChecked(Settings->GetBool("HideBar"));
        ui->LockPosCheckBox->setChecked(Settings->GetBool("LockPos"));

        ui->PosXEdit->setText(QString::number(Settings->GetVec("Pos").x()));
        ui->PosYEdit->setText(QString::number(Settings->GetVec("Pos").y()));

        ui->SizeXEdit->setText(QString::number(Settings->GetVec("Size").x()));
        ui->SizeYEdit->setText(QString::number(Settings->GetVec("Size").y()));

        ui->AutoCheckBox->setChecked(Settings->GetBool("AutoLoad"));
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
    this->hide();

    qApp->exit(1337);
}

void SettingsDialog::on_AcceptButton_clicked()
{
    Settings->Set("RememberPos", ui->RemPosCheckBox->checkState());
    Settings->Set("HideWin", ui->HideCheckBox->checkState());
    Settings->Set("HideBar", ui->HideBarCheckBox->checkState());
    Settings->Set("LockPos", ui->LockPosCheckBox->checkState());

    Settings->Set("Pos", QVector2D(ui->PosXEdit->text().toInt(), ui->PosYEdit->text().toInt()));
    Settings->Set("Size", QVector2D(ui->SizeXEdit->text().toInt(), ui->SizeYEdit->text().toInt()));

    Settings->Set("AutoMode",ui->AutoCheckBox->checkState());
    Settings->Set("LinkHistory",ui->DialDisplay->text());
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
