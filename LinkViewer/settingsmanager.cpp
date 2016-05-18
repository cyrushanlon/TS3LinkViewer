#include "settingsmanager.h"

#include <QFile>
#include <QFileInfo>

SettingsManager::SettingsManager()
{

}

void SettingsManager::LoadFile()
{
    QFileInfo CheckFile(FilePath);

    if (CheckFile.exists() && CheckFile.isFile())
    {
        QFile ExistingFile(FilePath);
        ExistingFile.open(QIODevice::ReadOnly);

        int i = 0;

        QTextStream InStream(&ExistingFile);
        while(!InStream.atEnd())
        {
            QString Line = InStream.readLine();

            if (i == 0)
                this->AutoLoad = Line == "true";
            else if (i == 1)
                this->HistoryLength = Line.toInt();
            else if (i == 2)
                this->OpenHotkey = Line;
            else if (i == 3)
                this->CloseHotkey = Line;
            else if (i == 4)
                this->AutoHotkey = Line;

            i++;
        }

        ExistingFile.close();
    }
    else
    {
        QFile NewFile(FilePath);
        NewFile.open(QIODevice::WriteOnly);

        QTextStream OutStream(&NewFile);

        OutStream   << "true\n"
                    << "10\n"
                    << "ctrl+alt+Right\n"
                    << "ctrl+alt+Left\n"
                    << "ctrl+alt+Down\n";
        NewFile.close();

        LoadFile();
    }
}

void SettingsManager::SaveFile()
{
    QFile NewFile(FilePath);
    NewFile.open(QIODevice::WriteOnly);

    QTextStream OutStream(&NewFile);

    OutStream   << this->AutoLoad << "\n"
                << this->HistoryLength << "\n"
                << this->OpenHotkey << "\n"
                << this->CloseHotkey << "\n"
                << this->AutoHotkey << "\n";
    NewFile.close();
}
