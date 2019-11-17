#include "mainmenu.h"
#include "settings.h"

#include <QDebug>

#include <QMenu>
#include <QApplication>
#include <QStandardPaths>

MainMenu::MainMenu(QObject* parent):QSystemTrayIcon(parent){
    disp = XOpenDisplay(nullptr);
    profiles = new QActionGroup(this);
    // build ui
    QIcon icon = QIcon::fromTheme("video-display");
    setIcon(icon);
    menu = new QMenu();
    QAction* exit = new QAction(QIcon::fromTheme("application-exit"), "Exit", this);
    QAction* settings = new QAction(QIcon::fromTheme("configure"), "Settings", this);
    separator = menu->addSeparator();
    menu->addAction(settings);
    menu->addAction(exit);
    loadModels();
    setContextMenu(menu);
    // connect
    connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(settings, SIGNAL(triggered()), this, SLOT(onSettings()));
    connect(profiles, SIGNAL(triggered(QAction*)), this, SLOT(profileSelected(QAction*)));
}

MainMenu::~MainMenu(){
    delete menu;
    XCloseDisplay(disp);
}

void MainMenu::onSettings(){
    Settings* settings = new Settings();
    if (settings->exec()){
        settings->saveSettings();
        loadModels();
    }
    delete settings;
}

void MainMenu::loadModels(){
    if (profileModel)
        delete profileModel;
    if (triggerModel)
        delete triggerModel;
    profileModel = new ProfileModel(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/profiles.json", this);
    triggerModel = new TriggerModel(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/triggers.json", profileModel, this);
    // clear profiles
    for (QAction* action:profiles->actions()){
        menu->removeAction(action);
        profiles->removeAction(action);
        delete action;
    }
    for (int i = 0; i < profileModel->rowCount(); i++){
        QAction* action = new QAction(profileModel->index(i).data().toString(), this);
        action->setCheckable(true);
        menu->insertAction(separator, action);
        profiles->addAction(action);
    }
}

void MainMenu::profileSelected(QAction* action){
    QModelIndex profile = profileModel->find(action->text());
    qDebug()<<profile.data(ProfileModel::StandbyRole).toUInt() << " " << profile.data(ProfileModel::SuspendRole).toUInt() << " " << profile.data(ProfileModel::OffRole).toUInt() << "\n";
    DPMSEnable(disp);
    DPMSSetTimeouts(disp, profile.data(ProfileModel::StandbyRole).toUInt()*60, profile.data(ProfileModel::SuspendRole).toUInt()*60, profile.data(ProfileModel::OffRole).toUInt()*60);
    //DPMSSetTimeouts(disp, 0, 0, 0);
    if (profile.data(ProfileModel::AwakeRole).toBool())
        DPMSForceLevel(disp, DPMSModeOn);
    XFlush(disp);
}
