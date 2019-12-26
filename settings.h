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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include "profilemodel.h"
#include "triggermodel.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings() override;
    void saveSettings();

public slots:
    void done(int r) override;

private slots:
    void on_profEdit_clicked();

    void on_profAdd_clicked();

    void on_profRemove_clicked();

    void on_trigEdit_clicked();

    void on_trigAdd_clicked();

    void on_trigRemove_clicked();

    void on_profiles_doubleClicked(const QModelIndex &index);

    void on_triggers_doubleClicked(const QModelIndex &index);

private:
    Ui::Settings *ui;
    ProfileModel* profileModel;
    TriggerModel* triggerModel;

};

#endif // SETTINGS_H
