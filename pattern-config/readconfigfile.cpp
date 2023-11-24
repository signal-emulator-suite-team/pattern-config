#include "readconfigfile.h"

ReadConfigFile::ReadConfigFile()
{

}
ReadConfigFile::~ReadConfigFile()
{

}

Config ReadConfigFile::getConfig(QString fileUrl)
{
    Config config;

    QFile file(fileUrl);

    if (!file.open(QIODevice::ReadOnly))
    {
        return config;
    }

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &jsonError);

    if (document.isNull() || (jsonError.error != QJsonParseError::NoError))
    {
        return config;
    }

    QJsonObject configObject = document.object();

    if (configObject.contains("ImageFile"))
    {
        QJsonValue value = configObject.value("ImageFile");
        config.imageFile = configObject.value("ImageFile").toString();
    }

    if (configObject.contains("Regions"))
    {
        QJsonArray regionArray = configObject.value("Regions").toArray();
        int regionArraySize = regionArray.size();

        for (int i = 0; i < regionArraySize; ++i)
        {
            Region region;
            QJsonObject regionObject = regionArray.at(i).toObject();

            if (regionObject.contains("Category"))
            {
                region.category = regionObject.value("Category").toString();
            }
            if (regionObject.contains("Prefix"))
            {
                region.prefix = regionObject.value("Prefix").toString();
            }
            if (regionObject.contains("Suffix"))
            {
                region.suffix = regionObject.value("Suffix").toString();
            }
            if (regionObject.contains("Channel"))
            {
                region.channel = regionObject.value("Channel").toString();
            }
            if (regionObject.contains("DirH"))
            {
                region.dirH = regionObject.value("DirH").toInt();
            }
            if (regionObject.contains("DirV"))
            {
                region.dirV = regionObject.value("DirV").toInt();
            }
            if (regionObject.contains("IndexStart"))
            {
                region.indexStart = regionObject.value("IndexStart").toInt();
            }
            if (regionObject.contains("ROI"))
            {
                QJsonArray roiArray = regionObject.value("ROI").toArray();
                int roiArraySize = roiArray.size();

                for (int i = 0; i < roiArraySize; i++)
                {
                    region.roi[i] = roiArray.at(i).toInt();
                }
            }

            config.regions.append(region);
        }
    }

    return config;
}
