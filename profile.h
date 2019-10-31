#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include <QJsonObject>

class Profile
{
public:
    Profile(const QString& name, uint16_t standby, uint16_t suspend, uint16_t off, bool awake);
    Profile(const QJsonObject& data);
    QJsonObject toJson() const;
    QString name() const;
    uint16_t standby() const;
    uint16_t suspend() const;
    uint16_t off() const;
    bool awake() const;
    void setName(const QString& name);
    void setStandby(uint16_t standby);
    void setSuspend(uint16_t suspend);
    void setOff(uint16_t off);
    void setAwake(bool awake);

private:
    QString _name;
    uint16_t _standby;
    uint16_t _suspend;
    uint16_t _off;
    bool _awake;

};

#endif // PROFILE_H
