#include "mainmenu.h"
#include "settings.h"

#include <QDebug>

#include <QMenu>
#include <QApplication>
#include <QStandardPaths>
#include <QTimer>

MainMenu::MainMenu(QObject* parent):QSystemTrayIcon(parent){
    disp = XOpenDisplay(nullptr);
    profiles = new QActionGroup(this);
    // build ui
    QIcon icon = QIcon::fromTheme("computer");
    setIcon(icon);
    menu = new QMenu();
    QAction* exit = new QAction(QIcon::fromTheme("application-exit"), "Exit", this);
    QAction* settings = new QAction(QIcon::fromTheme("configure"), "Settings", this);
    separator = menu->addSeparator();
    menu->addAction(settings);
    menu->addAction(exit);
    loadModels();
    setContextMenu(menu);
    timer = new QTimer(this);
    planAction();
    // connect
    connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(settings, SIGNAL(triggered()), this, SLOT(onSettings()));
    connect(profiles, SIGNAL(triggered(QAction*)), this, SLOT(profileSelected(QAction*)));
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
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
        planAction();
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
    DPMSEnable(disp);
    DPMSSetTimeouts(disp, profile.data(ProfileModel::StandbyRole).toUInt()*60, profile.data(ProfileModel::SuspendRole).toUInt()*60, profile.data(ProfileModel::OffRole).toUInt()*60);
    if (profile.data(ProfileModel::AwakeRole).toBool())
        DPMSForceLevel(disp, DPMSModeOn);
    XFlush(disp);
}

void MainMenu::planAction(){
    timer->stop();
    if (triggerModel->rowCount() == 0)
        return;
    int64_t timeout = triggerModel->index(0).data(TriggerModel::TimeoutRole).toLongLong();
    QString profile = triggerModel->index(0).data(TriggerModel::ProfileRole).toPersistentModelIndex().data().toString();
    for (int i = 0; i < triggerModel->rowCount(); i++){
        if (triggerModel->index(i).data(TriggerModel::TimeoutRole).toLongLong() < timeout){
            timeout = triggerModel->index(i).data(TriggerModel::TimeoutRole).toLongLong();
            profile = triggerModel->index(i).data(TriggerModel::ProfileRole).toPersistentModelIndex().data().toString();
        }
    }
    // schedule timer
    profileToActivate = profile;
    timer->start(timeout);
}

void MainMenu::onTimer(){
    for (QAction* action: profiles->actions()){
        if (action->text() == profileToActivate){
            action->activate(QAction::Trigger);
            planAction();
            return;
        }
    }
    planAction();
}
