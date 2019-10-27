#ifndef MAINMENU_H
#define MAINMENU_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

class MainMenu : public QSystemTrayIcon
{
public:
    MainMenu(QObject *parent = nullptr);
    ~MainMenu();
    QMenu* menu;
};

#endif // MAINMENU_H
