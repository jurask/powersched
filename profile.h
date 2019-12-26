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
