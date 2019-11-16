#include "trigger.h"


Trigger::Trigger(const QTime& time, const QBitArray& weekdays, QModelIndex profile){
    _time = time;
    _weekdays = weekdays;
    _profile = QPersistentModelIndex(profile);
}

Trigger::Trigger(const QJsonObject data, ProfileModel* profiles){
    if (!data.contains("time") || !data.contains("monday") || !data.contains("tuesday") || !data.contains("wednesday") || !data.contains("thursday") || !data.contains("friday") || !data.contains("saturday") || !data.contains("sunday") || !data.contains("profile"))
        return;
    if (data["time"].isString()){
        _time = QTime::fromString(data["time"].toString(), "hh:mm:ss");
        if (!_time.isValid())
            return;
    }
    else
        return;
    _weekdays = QBitArray(7, false);
    if (data["monday"].isBool())
        _weekdays[0] = data["monday"].toBool();
    else
        return;
    if (data["tuesday"].isBool())
        _weekdays[1] = data["tuesday"].toBool();
    else
        return;
    if (data["wednesday"].isBool())
        _weekdays[2] = data["wednesday"].toBool();
    else
        return;
    if (data["thursday"].isBool())
        _weekdays[3] = data["thursday"].toBool();
    else
        return;
    if (data["friday"].isBool())
        _weekdays[4] = data["friday"].toBool();
    else
        return;
    if (data["saturday"].isBool())
        _weekdays[5] = data["saturday"].toBool();
    else
        return;
    if (data["sunday"].isBool())
        _weekdays[6] = data["sunday"].toBool();
    else
        return;
    if (data["profile"].isString()){
        QModelIndex index = profiles->find(data["profile"].toString());
        _profile = QPersistentModelIndex(index);
    } else
        return;
}

QJsonObject Trigger::toJson() const{
    QJsonObject result;
    result.insert("time", QJsonValue(_time.toString("HH:mm:ss")));
    result.insert("monday", _weekdays[0]);
    result.insert("tuesday", _weekdays[1]);
    result.insert("wednesday", _weekdays[2]);
    result.insert("thursday", _weekdays[3]);
    result.insert("friday", _weekdays[4]);
    result.insert("saturday", _weekdays[5]);
    result.insert("sunday", _weekdays[6]);
    result.insert("profile", _profile.data(Qt::DisplayRole).toString());
    return result;
}

QTime Trigger::time() const{
    return _time;
}

bool Trigger::weekday(uint8_t day) const{
    return _weekdays[day];
}

QPersistentModelIndex Trigger::profile() const{
    return _profile;
}

QString Trigger::name() const{
    QString profileName;
    if (_profile.isValid())
        profileName = _profile.data(Qt::DisplayRole).toString();
    else
        profileName = "???";
    QString weekdays;
    if (_weekdays[0])
        weekdays += " Mo";
    if (_weekdays[1])
        weekdays += " Tu";
    if (_weekdays[2])
        weekdays += " We";
    if (_weekdays[3])
        weekdays += " Th";
    if (_weekdays[4])
        weekdays += " Fr";
    if (_weekdays[5])
        weekdays += " Sat";
    if (_weekdays[6])
        weekdays += " Sun";
    QString time = _time.toString("HH:mm");
    return profileName+":"+weekdays+" "+time;
}

bool Trigger::valid() const{
    return _profile.isValid();
}

void Trigger::setTime(const QTime &time){
    _time = time;
}

bool Trigger::setWeekday(uint8_t day, bool value){
    if (day < 7){
        _weekdays[day] = value;
        return true;
    } else
        return false;
}

bool Trigger::setProfile(const QModelIndex profile){
    if (profile.isValid()){
        _profile = QPersistentModelIndex(profile);
        return true;
    } else
        return false;
}
