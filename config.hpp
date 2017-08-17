#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class Config {
public:
    Config(QJsonObject& arr)
    {
        mapping(arr);
    }

    void mapping(QJsonObject& obj)
    {
        QJsonArray arr = obj["configuration"].toArray();
        foreach(const QJsonValue& it, arr)
        {
            QJsonObject val = it.toObject();
            map.insert(val["name"].toString(), val["command"].toString());
        }
    }
    QMap<QString, QString> map;
};

#endif // CONFIG_HPP
