#ifndef MAINMENU_H
#define MAINMENU_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

class MainMenu : public QSystemTrayIcon
{
Q_OBJECT

public:
    MainMenu(QObject *parent = nullptr);
    ~MainMenu();
    QMenu* menu;

public slots:
    void onSettings();
};

#endif // MAINMENU_H
