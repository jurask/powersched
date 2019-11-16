#ifndef TRIGGER_H
#define TRIGGER_H

#include <QBitArray>
#include <QTime>
#include <QPersistentModelIndex>

#include "profilemodel.h"

class Trigger
{
public:
    Trigger(const QTime& time, const QBitArray& weekdays, QModelIndex profile);
    Trigger(const QJsonObject data, ProfileModel* profiles);
    QJsonObject toJson() const;
    QTime time() const;
    bool weekday(uint8_t day) const;
    QPersistentModelIndex profile() const;
    QString name() const;
    bool valid() const;
    void setTime(const QTime& time);
    bool setWeekday(uint8_t day, bool value);
    bool setProfile(const QModelIndex profile);

private:
    QTime _time;
    QBitArray _weekdays;
    QPersistentModelIndex _profile;
};

#endif // TRIGGER_H
