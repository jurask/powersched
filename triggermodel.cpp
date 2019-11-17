#include "triggermodel.h"
#include "trigger.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

TriggerModel::TriggerModel(QObject *parent) : QAbstractListModel(parent){
}

TriggerModel::TriggerModel(const QString& filename, ProfileModel* profiles, QObject *parent):QAbstractListModel(parent){
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
            Trigger trigger(value.toObject(), profiles);
            _data.append(trigger);
        }
    }
}

bool TriggerModel::save(const QString& filename) const{
    QJsonArray array;
    for (const Trigger& trigger:_data){
        if (trigger.valid())
            array.append(QJsonValue(trigger.toJson()));
    }
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

bool TriggerModel::valid() const{
    for (const Trigger& trigger:_data){
        if (!trigger.valid())
            return false;
    }
    return true;
}

void TriggerModel::append(const Trigger& trigger){
    beginInsertRows(QModelIndex(), _data.length(), _data.length()+1);
    _data.append(trigger);
    endInsertRows();
}


QVariant TriggerModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (section != 0 || orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();
    else
        return QVariant("trigger");
}


int TriggerModel::rowCount(const QModelIndex& parent) const{
    if (parent.isValid())
        return 0;
    return _data.size();
}

QVariant TriggerModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
        return QVariant(_data[index.row()].name());
    if (role == TriggerRole::TimeRole)
        return QVariant(_data[index.row()].time());
    if (role == TriggerRole::MondayRole)
        return QVariant(_data[index.row()].weekday(0));
    if (role == TriggerRole::TuesdayRole)
        return QVariant(_data[index.row()].weekday(1));
    if (role == TriggerRole::WednesdayRole)
        return QVariant(_data[index.row()].weekday(2));
    if (role == TriggerRole::ThursdayRole)
        return QVariant(_data[index.row()].weekday(3));
    if (role == TriggerRole::FridayRole)
        return QVariant(_data[index.row()].weekday(4));
    if (role == TriggerRole::SaturdayRole)
        return QVariant(_data[index.row()].weekday(5));
    if (role == TriggerRole::SundayRole)
        return QVariant(_data[index.row()].weekday(6));
    if (role == TriggerRole::ProfileRole)
        return QVariant(_data[index.row()].profile());
    if (role == TriggerRole::TimeoutRole){
        QDateTime now = QDateTime::currentDateTime();
        int weekday = now.date().dayOfWeek()-1;
        for (uint8_t i = 0; i < 8; i++){
            uint8_t dayToProbe = (weekday+i)%7;
            if (_data[index.row()].weekday(dayToProbe)){
                if (i == 0){
                    if (now.time() > _data[index.row()].time())
                        continue;
                }
                // found day
                QDateTime event = QDateTime(now.date().addDays(i), _data[index.row()].time());
                return event.toMSecsSinceEpoch()-now.toMSecsSinceEpoch();
            }
        }
    }
    return QVariant();
}

bool TriggerModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if (data(index, role) != value) {
        if (role == TriggerRole::TimeRole)
            _data[index.row()].setTime(value.toTime());
        else if (role == TriggerRole::MondayRole)
            _data[index.row()].setWeekday(0, value.toBool());
        else if (role == TriggerRole::TuesdayRole)
            _data[index.row()].setWeekday(1, value.toBool());
        else if (role == TriggerRole::WednesdayRole)
            _data[index.row()].setWeekday(2, value.toBool());
        else if (role == TriggerRole::ThursdayRole)
            _data[index.row()].setWeekday(3, value.toBool());
        else if (role == TriggerRole::FridayRole)
            _data[index.row()].setWeekday(4, value.toBool());
        else if (role == TriggerRole::SaturdayRole)
            _data[index.row()].setWeekday(5, value.toBool());
        else if (role == TriggerRole::SundayRole)
            _data[index.row()].setWeekday(6, value.toBool());
        else if (role == TriggerRole::ProfileRole)
            _data[index.row()].setProfile(value.toPersistentModelIndex());
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

bool TriggerModel::removeRows(int row, int count, const QModelIndex &parent){
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++)
        _data.removeAt(row);
    endRemoveRows();
    return true;
}
