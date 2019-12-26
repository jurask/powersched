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

#ifndef PROFILEMODEL_H
#define PROFILEMODEL_H

#include <QAbstractListModel>

#include "profile.h"

class ProfileModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ProfileRole{
        StandbyRole = Qt::UserRole + 1,
        SuspendRole = Qt::UserRole + 2,
        OffRole = Qt::UserRole + 3,
        AwakeRole = Qt::UserRole + 4
    };
    explicit ProfileModel(QObject *parent = nullptr);
    ProfileModel(const QString& filename, QObject *parent = nullptr);
    bool contains(const QString& name) const;
    QModelIndex find(const QString& name) const;
    bool save(const QString& filename) const;
    void append(const Profile& profile);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    QList<Profile> _data;
};

#endif // PROFILEMODEL_H
