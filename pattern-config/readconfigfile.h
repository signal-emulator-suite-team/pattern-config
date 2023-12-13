#ifndef READCONFIGFILE_H
#define READCONFIGFILE_H

#include <QString>
#include <QList>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

struct Region
{
    QString category;
    QString channel;
    int dirH;
    int dirV;
    QString prefix;
    QString suffix;
    int indexStart;
    int indexEnd;
    int roi[4];
};

struct Config
{
    QString imageFile;
    QList<Region> regions;
};

class ReadConfigFile
{
public:
    ReadConfigFile();
    ~ReadConfigFile();
    Config getConfig(QString fileUrl);

private:
    QString m_fileUrl;
};

#endif // READCONFIGFILE_H
