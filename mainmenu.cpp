#include "mainmenu.h"
#include "settings.h"

#include <QMenu>
#include <QApplication>

MainMenu::MainMenu(QObject* parent):QSystemTrayIcon(parent){
    // build ui
    QIcon icon = QIcon::fromTheme("video-display");
    setIcon(icon);
    menu = new QMenu();
    QAction* exit = new QAction(QIcon::fromTheme("application-exit"), "Exit", this);
    QAction* settings = new QAction(QIcon::fromTheme("configure"), "Settings", this);
    menu->addAction(settings);
    menu->addAction(exit);
    setContextMenu(menu);
    // connect
    connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(settings, SIGNAL(triggered()), this, SLOT(onSettings()));
}

MainMenu::~MainMenu(){
    delete menu;
}

void MainMenu::onSettings(){
    Settings* settings = new Settings();
    if (settings->exec())
        settings->saveSettings();
    delete settings;
}
