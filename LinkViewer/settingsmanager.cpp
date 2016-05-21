#include "settingsmanager.h"

#include <QFile>
#include <QFileInfo>

//Remember Pos
//Remember Size
//No fixed win
//Lock win
//Pos xy
//size xy
//auto mode
//link history
//Hotkey open
//Hotkey close
//Hotkey auto

SettingsManager::SettingsManager()
{
    LoadFile();
}

QString SettingsManager::Get(QString Key)
{
    if (Map.contains(Key))
        return Map[Key];
    else
        return NULL;
}

QVector2D SettingsManager::GetVec(QString Key)
{
    if (Map.contains(Key))
    {
        QStringList Split = Map[Key].split(";");
        return QVector2D(Split[0].toInt(), Split[1].toInt());
    }
    else
        return QVector2D();
}

bool SettingsManager::GetBool(QString Key)
{
    if (Map.contains(Key))
        return Map[Key] == "1";
    else
        return NULL;
}

int SettingsManager::GetInt(QString Key)
{
    if (Map.contains(Key))
        return Map[Key].toInt();
    else
        return NULL;
}

void SettingsManager::Set(QString Key, QString Val)
{
    Map[Key] = Val;
}

void SettingsManager::Set(QString Key, QVector2D Val)
{
    Map[Key] = QString::number(Val.x()) + ";" + QString::number(Val.y());
}

void SettingsManager::Set(QString Key, QPoint Val)
{
    Map[Key] = QString::number(Val.x()) + ";" + QString::number(Val.y());
}

void SettingsManager::Set(QString Key, bool Val)
{
    if (Val)
        Map[Key] == "1";
    else
        Map[Key] == "0";

}

void SettingsManager::LoadFile()
{

    QFileInfo CheckFile(FilePath);

    if (CheckFile.exists() && CheckFile.isFile())
    {
        QFile ExistingFile(FilePath);
        ExistingFile.open(QIODevice::ReadOnly);

        QTextStream InStream(&ExistingFile);
        while(!InStream.atEnd())
        {
            QStringList Line = InStream.readLine().split(",");

            Set(Line[0], Line[1]);
        }

        ExistingFile.close();
    }
    else
    {
        QFile NewFile(FilePath);
        NewFile.open(QIODevice::WriteOnly);

        QTextStream OutStream(&NewFile);

        OutStream << "RememberPos,0";
        OutStream << "RememberSize,0";
        OutStream << "FixedWin,0";
        OutStream << "LockWin,0";
        OutStream << "AutoMode,1";
        OutStream << "LinkHistory,10";
        OutStream << "HotkeyOpen,ctrl+shift+Right";
        OutStream << "HotkeyClose,ctrl+shift+Left";
        OutStream << "HotkeyAuto,ctrl+shift+Down";

        NewFile.close();

        LoadFile();
    }
}

void SettingsManager::SaveFile()
{
    QFile NewFile(FilePath);
    NewFile.open(QIODevice::WriteOnly);

    QTextStream OutStream(&NewFile);

    QStringList Keys = Map.keys();

    foreach(const QString &Key, Map.keys())
    {
        OutStream << Key << "," << Map[Key] << "\n";
    }

    NewFile.close();
}

