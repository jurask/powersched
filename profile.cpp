#include "profile.h"

Profile::Profile(const QString &name, uint16_t standby, uint16_t suspend, uint16_t off, bool awake){
    _name = name;
    _standby = standby;
    _suspend = suspend;
    _off = off;
    _awake = awake;
}

Profile::Profile(const QJsonObject& data){
    _name = "";
    if (!data.contains("name") || !data.contains("standby") || !data.contains("suspend") || !data.contains("off") || !data.contains("awake"))
        return;
    if (data["standby"].isDouble())
        _standby = data["standby"].toInt();
    else
        return;
    if (data["suspend"].isDouble())
        _suspend = data["suspend"].toInt();
    else
        return;
    if (data["off"].isDouble())
        _off = data["off"].toInt();
    else
        return;
    if (data["awake"].isBool())
        _awake = data["awake"].toBool();
    else
        return;
    if (data["name"].isString())
        _name = data["name"].toString();
    else
        return;
}

QJsonObject Profile::toJson() const{
    QJsonObject result;
    result.insert("name", QJsonValue(_name));
    result.insert("standby", QJsonValue(_standby));
    result.insert("suspend", QJsonValue(_suspend));
    result.insert("off", QJsonValue(_off));
    result.insert("awake", QJsonValue(_awake));
    return result;
}

QString Profile::name() const{
    return _name;
}

uint16_t Profile::standby() const{
    return _standby;
}

uint16_t Profile::suspend() const{
    return _suspend;
}

uint16_t Profile::off() const{
    return _off;
}

bool Profile::awake() const{
    return _awake;
}

void Profile::setName(const QString &name){
    _name = name;
}

void Profile::setStandby(uint16_t standby){
    _standby = standby;
}

void Profile::setSuspend(uint16_t suspend){
    _suspend = suspend;
}

void Profile::setOff(uint16_t off){
    _off = off;
}

void Profile::setAwake(bool awake){
    _awake = awake;
}
