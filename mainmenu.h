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
