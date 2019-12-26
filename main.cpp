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

#include <QApplication>
#include <QMessageBox>

#include "mainmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    QCoreApplication::setOrganizationName("jurask");
    QCoreApplication::setApplicationName("powershed");
    Display* disp = XOpenDisplay(nullptr);
    if (disp == nullptr){
        QMessageBox::critical(nullptr, "Error", "Unable to open dislpay");
        return 0;
    }
    if (!DPMSCapable(disp)){
        QMessageBox::critical(nullptr, "Error", "Display Power Management Signaling not available");
        return 0;
    }
    XCloseDisplay(disp);
    MainMenu menu;
    menu.show();
    return a.exec();
}
