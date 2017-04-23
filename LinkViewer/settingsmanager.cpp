#include "settingsmanager.h"

#include <QFile>
#include <QFileInfo>

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

QSize SettingsManager::GetSize(QString Key)
{
    if (Map.contains(Key))
    {
        QStringList Split = Map[Key].split(";");
        return QSize(Split[0].toInt(), Split[1].toInt());
    }
    else
        return QSize();
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
    Map.insert(Key, Val);
}

void SettingsManager::Set(QString Key, QVector2D Val)
{    
    Map.insert(Key, QString::number(Val.x()) + ";" + QString::number(Val.y()));
}

void SettingsManager::Set(QString Key, QPoint Val)
{
    Map.insert(Key, QString::number(Val.x()) + ";" + QString::number(Val.y()));
}

void SettingsManager::Set(QString Key, QSize Val)
{
    Map.insert(Key, QString::number(Val.width()) + ";" + QString::number(Val.height()));
}

void SettingsManager::Set(QString Key, bool Val)
{
    QString Value;

    if (Val)
        Value = "1";
    else
        Value = "0";

    Map.insert(Key, Value);
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

        OutStream   << "RememberPos,0\n" //remember where the window is pos + size
                    << "Size,0;0\n"
                    << "Pos,0;0\n"
                    << "HideWin,0\n"
                    << "LockPos,0\n"
                    << "HideBar,0\n"
                    << "AutoLoad,1\n"
                    << "LinkHistory,10\n"
                    << "HotkeyOpen,ctrl+shift+Right\n"
                    << "HotkeyClose,ctrl+shift+Left\n"
                    << "HotkeyAuto,ctrl+shift+Down\n";

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

