#include "profilemodel.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

ProfileModel::ProfileModel(QObject *parent):QAbstractListModel(parent){
}

ProfileModel::ProfileModel(const QString& filename){
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

QVariant ProfileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section != 0 || orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();
    else
        return QVariant("name");
}

int ProfileModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return _data.size();
}

QVariant ProfileModel::data(const QModelIndex &index, int role) const
{
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

bool ProfileModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++)
        _data.removeAt(row);
    endRemoveRows();
}
