/*
 * Powersched
 * Copyright (C) 2019 Jiri Babocky
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
