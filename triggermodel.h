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

#ifndef TRIGGERMODEL_H
#define TRIGGERMODEL_H

#include <QAbstractListModel>
#include "profilemodel.h"
#include "trigger.h"

class TriggerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum TriggerRole{
        TimeRole = Qt::UserRole + 1,
        MondayRole = Qt::UserRole + 2,
        TuesdayRole = Qt::UserRole + 3,
        WednesdayRole = Qt::UserRole + 4,
        ThursdayRole = Qt::UserRole + 5,
        FridayRole = Qt::UserRole + 6,
        SaturdayRole = Qt::UserRole + 7,
        SundayRole = Qt::UserRole + 8,
        ProfileRole = Qt::UserRole + 9,
        TimeoutRole = Qt::UserRole + 10
    };
    explicit TriggerModel(QObject *parent = nullptr);
    TriggerModel(const QString& filename, ProfileModel* profiles, QObject *parent = nullptr);
    bool valid() const;
    bool save(const QString& filename) const;
    void append(const Trigger& trigger);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    QList<Trigger> _data;
};

#endif // TRIGGERMODEL_H
