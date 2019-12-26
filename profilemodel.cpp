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

#include "profilemodel.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

ProfileModel::ProfileModel(QObject *parent):QAbstractListModel(parent){
}

ProfileModel::ProfileModel(const QString& filename, QObject *parent):QAbstractListModel(parent){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QByteArray bytes = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(bytes);
    if (!document.isArray())
        return;
    for (QJsonValueRef value:document.array()){
        if (value.isObject()){
            Profile profile(value.toObject());
            if (profile.name() != "" && !contains(profile.name()))
                _data.append(profile);
        }
    }
}

bool ProfileModel::contains(const QString &name) const{
    bool found = false;
    for (const Profile& profile:_data){
        if (profile.name() == name){
            found = true;
            break;
        }
    }
    return found;
}

QModelIndex ProfileModel::find(const QString& name) const{
    int row = 0;
    for (const Profile& profile:_data){
        if (profile.name() == name)
            return index(row);
        row++;
    }
    return QModelIndex();
}

bool ProfileModel::save(const QString &filename) const{
    QJsonArray array;
    for (const Profile& profile:_data)
        array.append(QJsonValue(profile.toJson()));
    QJsonDocument document(array);
    QByteArray bytes = document.toJson(QJsonDocument::Indented);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    if (file.write(bytes) == -1){
        file.close();
        return false;
    }
    file.close();
    return true;
}

QVariant ProfileModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (section != 0 || orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();
    else
        return QVariant("name");
}

int ProfileModel::rowCount(const QModelIndex &parent) const{
    if (parent.isValid())
        return 0;
    return _data.size();
}

QVariant ProfileModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
        return QVariant(_data[index.row()].name());
    else if (role == StandbyRole)
        return QVariant(_data[index.row()].standby());
    else if (role == SuspendRole)
        return QVariant(_data[index.row()].suspend());
    else if (role == OffRole)
        return QVariant(_data[index.row()].off());
    else if (role == AwakeRole)
        return QVariant(_data[index.row()].awake());
    return QVariant();
}

bool ProfileModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if (!index.isValid() || index.column() != 0 || index.row() >= _data.size())
        return false;
    if (role == Qt::DisplayRole){
        _data[index.row()].setName(value.toString());
        emit dataChanged(index, index);
        return true;
    } else if (role == ProfileRole::StandbyRole){
        _data[index.row()].setStandby(value.toUInt());
        emit dataChanged(index, index);
        return true;
    } else if (role == ProfileRole::SuspendRole){
        _data[index.row()].setSuspend(value.toUInt());
        emit dataChanged(index, index);
        return true;
    } else if (role == ProfileRole::OffRole){
        _data[index.row()].setOff(value.toUInt());
        emit dataChanged(index, index);
        return true;
    } else if (role == ProfileRole::AwakeRole){
        _data[index.row()].setAwake(value.toBool());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool ProfileModel::removeRows(int row, int count, const QModelIndex &parent){
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++)
        _data.removeAt(row);
    endRemoveRows();
    return true;
}

void ProfileModel::append(const Profile &profile){
    beginInsertRows(QModelIndex(), _data.length(), _data.length()+1);
    _data.append(profile);
    endInsertRows();
}
