#ifndef PROFILEMODEL_H
#define PROFILEMODEL_H

#include <QAbstractListModel>

#include "profile.h"

class ProfileModel : public QAbstractListModel
{
    Q_OBJECT

    enum ProfileRole{
        StandbyRole = Qt::UserRole + 1,
        SuspendRole = Qt::UserRole + 2,
        OffRole = Qt::UserRole + 3,
        AwakeRole = Qt::UserRole + 4
    };

public:
    explicit ProfileModel(QObject *parent = nullptr);
    ProfileModel(const QString& filename);
    bool contains(const QString& name) const;
    bool save(const QString& filename) const;

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    QList<Profile> _data;
};

#endif // PROFILEMODEL_H
