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

#ifndef PROFILEEDIT_H
#define PROFILEEDIT_H

#include <QDialog>
#include "profilemodel.h"

namespace Ui {
class ProfileEdit;
}

class ProfileEdit : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileEdit(ProfileModel *model, QWidget *parent = nullptr);
    void setData(const QString& name, uint16_t standby, uint16_t suspend, uint16_t off, bool awake);
    ~ProfileEdit() override;
    QString name() const;
    uint16_t standby() const;
    uint16_t suspend() const;
    uint16_t off() const;
    bool awake() const;

public slots:
    void done(int r) override;

private:
    Ui::ProfileEdit *ui;
    ProfileModel* _model;
    QString originalName;
};

#endif // PROFILEEDIT_H
