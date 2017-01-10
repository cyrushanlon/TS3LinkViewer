#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "settingsmanager.h"

#include <QWidget>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    void SetSettings(SettingsManager* SettingsIn)
    {
        Settings = SettingsIn;
    }

private slots:
    void on_DiscardButton_clicked();
    void on_AcceptButton_clicked();
    void on_LinkCountDial_sliderMoved(int position);

private:
    Ui::SettingsDialog *ui;
    void showEvent(QShowEvent *);

    SettingsManager* Settings;
};

#endif // SETTINGSDIALOG_H
