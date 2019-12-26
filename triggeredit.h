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

#ifndef TRIGGEREDIT_H
#define TRIGGEREDIT_H

#include <QDialog>

#include "profilemodel.h"

namespace Ui {
class TriggerEdit;
}

class TriggerEdit : public QDialog
{
    Q_OBJECT

public:
    explicit TriggerEdit(ProfileModel* profiles, QWidget *parent = nullptr);
    void setData(const QPersistentModelIndex& profile, const QTime& time, bool mo, bool tu, bool we, bool th, bool fr, bool sa, bool su);
    QTime time() const;
    bool weekday(uint8_t day) const;
    QModelIndex profile() const;
    ~TriggerEdit() override;

public slots:
    void done(int r) override;

private:
    Ui::TriggerEdit *ui;
};

#endif // TRIGGEREDIT_H
