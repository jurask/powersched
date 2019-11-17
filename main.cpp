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
