#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include<QtCore>

class SettingsManager
{
public:
    SettingsManager();

    int HistoryLength;

    bool AutoLoad;

    QString OpenHotkey;
    QString CloseHotkey;
    QString AutoHotkey;

    void LoadFile();
    void SaveFile();
private:
    QString FilePath = "LinkViewercfg";
};

#endif // SETTINGSMANAGER_H
