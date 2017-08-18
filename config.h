#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

class Config {
public:

    enum class RunType
    {
        Autostart,
        Manulay
    };
    Config()
    {
    }
    Config(QString name, QString command, RunType type)
    {
        this->name = name;
        this->command = command;
        this->runType = type;
    }

    QString name;
    QString command;
    RunType runType;
};

#endif // CONFIG_H
