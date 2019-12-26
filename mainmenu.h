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

#ifndef MAINMENU_H
#define MAINMENU_H

#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>
#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include "profilemodel.h"
#include "triggermodel.h"

class MainMenu : public QSystemTrayIcon
{
Q_OBJECT

public:
    MainMenu(QObject *parent = nullptr);
    ~MainMenu();
    QMenu* menu;

public slots:
    void onSettings();

private:
    ProfileModel* profileModel = nullptr;
    TriggerModel* triggerModel = nullptr;
    QActionGroup* profiles;
    QAction* separator;
    Display* disp;
    QTimer* timer;
    QString profileToActivate;
    void loadModels();

private slots:
    void profileSelected(QAction* action);
    void onTimer();
    void planAction();

};

#endif // MAINMENU_H
