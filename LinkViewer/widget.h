#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSharedMemory>
#include <QHotkey> //from https://github.com/Skycoder42/QHotkey

#include "settingsdialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void TimerPulse();
    void NotificationTimerPulse();
    void HandleToggleAuto();
    void HandleDeleteLink();
    void HandleOpenLink();
    void HandleCloseLink();

private:
    bool GetURLFromString(QString& Text);
    void UpdateURLList(QString URL);

    void CheckURLMemory();
    void CheckConfigMemory();

    void Load();

    Ui::Widget *ui;
    QSharedMemory SharedMemory;
    QSharedMemory ConfigMemory;

    QTimer *Timer;
    QTimer *NotificationTimer;

    int CurURLIndex = 0;

    QHotkey Hotkey_OpenLink;
    QHotkey Hotkey_DeleteLink;
    QHotkey Hotkey_ToggleAuto;
    QHotkey HotKey_CloseLink;

    SettingsDialog SettingsForm;
    SettingsManager* Settings;

protected:
    void resizeEvent(QResizeEvent *e);
    void closeEvent(QCloseEvent *e);
};

#endif // WIDGET_H
