#include "mainmenu.h"
#include <QMenu>
#include <QApplication>

MainMenu::MainMenu(QObject* parent):QSystemTrayIcon(parent){
    // build ui
    QIcon icon = QIcon::fromTheme("video-display");
    setIcon(icon);
    menu = new QMenu();
    QAction* exit = new QAction(QIcon::fromTheme("application-exit"), "Exit", this);
    menu->addAction(exit);
    setContextMenu(menu);
    // connect
    connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainMenu::~MainMenu(){
    delete menu;
}
