#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "config.h"
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class ParserConfig {
public:
    ParserConfig() = default;
    ~ParserConfig() = default;

    ParserConfig(QJsonObject& arr)
    {
        mapping(arr);
    }

    QMap<QString, Config> getMap() const
    {
        return map;
    }

    void mapping(QJsonObject& obj)
    {
        QJsonArray arr = obj["configuration"].toArray();
        foreach(const QJsonValue& it, arr)
        {
            QJsonObject val = it.toObject();
            Config conf(val["name"].toString(), val["command"].toString(), Config::RunType::Manulay);
            map.insert(conf.name, conf);
        }
    }

private:
    QMap<QString, Config> map;
};

#endif // CONFIG_HPP
