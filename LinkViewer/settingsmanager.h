#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QtCore>
#include <QHash>
#include <QVector2D>

class SettingsManager
{
public:
    SettingsManager();

    QString Get(QString Key);
    QVector2D GetVec(QString Key);
    QSize GetSize(QString Key);
    bool GetBool(QString Key);
    int GetInt(QString Key);

    void Set(QString Key, QString Val);
    void Set(QString Key, QVector2D Val);
    void Set(QString Key, QPoint Val);
    void Set(QString Key, QSize Val);
    void Set(QString Key, bool Val);

    void LoadFile();
    void SaveFile();
private:
    QString FilePath = "LinkViewercfg";

    QHash<QString, QString> Map;
};

#endif // SETTINGSMANAGER_H
