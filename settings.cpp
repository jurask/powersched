#include "settings.h"
#include "ui_settings.h"

#include <QStandardPaths>
#include <QMessageBox>
#include <QDir>

#include "profileedit.h"

Settings::Settings(QWidget *parent) : QDialog(parent), ui(new Ui::Settings){
    ui->setupUi(this);
    profileModel = new ProfileModel(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/profiles.json", this);
    ui->profiles->setModel(profileModel);
}

Settings::~Settings(){
    delete ui;
}

void Settings::saveSettings(){
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists())
        dir.mkpath(".");
    if (!profileModel->save(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/profiles.json"))
        QMessageBox::critical(this, "Error", "Error saving application settings");
}

void Settings::on_add_clicked(){
    ProfileEdit* editwin = new ProfileEdit(profileModel, this);
    if (editwin->exec()){
        Profile profile(editwin->name(), editwin->standby(), editwin->suspend(), editwin->off(), editwin->awake());
        profileModel->append(profile);
    }
    delete editwin;
}

void Settings::on_remove_clicked(){
    if (ui->profiles->currentIndex().isValid())
        profileModel->removeRows(ui->profiles->currentIndex().row(), 1);
}

void Settings::on_edit_clicked(){
    QModelIndex curentIndex = ui->profiles->currentIndex();
    if (curentIndex.isValid()){
        ProfileEdit* editwin = new ProfileEdit(profileModel, this);
        editwin->setData(curentIndex.data(Qt::DisplayRole).toString(), curentIndex.data(ProfileModel::StandbyRole).toUInt(), curentIndex.data(ProfileModel::SuspendRole).toUInt(), curentIndex.data(ProfileModel::OffRole).toUInt(), curentIndex.data((ProfileModel::AwakeRole)).toBool());
        if (editwin->exec()){
            profileModel->setData(curentIndex, editwin->name(), Qt::DisplayRole);
            profileModel->setData(curentIndex, editwin->standby(), ProfileModel::StandbyRole);
            profileModel->setData(curentIndex, editwin->suspend(), ProfileModel::SuspendRole);
            profileModel->setData(curentIndex, editwin->off(), ProfileModel::OffRole);
            profileModel->setData(curentIndex, editwin->awake(), ProfileModel::AwakeRole);
        }
        delete editwin;
    }
}
