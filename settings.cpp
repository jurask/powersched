#include "settings.h"
#include "ui_settings.h"

#include <QStandardPaths>
#include <QMessageBox>
#include <QDir>

#include "profileedit.h"
#include "triggeredit.h"

Settings::Settings(QWidget *parent) : QDialog(parent), ui(new Ui::Settings){
    ui->setupUi(this);
    profileModel = new ProfileModel(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/profiles.json", this);
    ui->profiles->setModel(profileModel);
    triggerModel = new TriggerModel(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/triggers.json", profileModel, this);
    ui->triggers->setModel(triggerModel);
}

Settings::~Settings(){
    delete ui;
}

void Settings::saveSettings(){
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists())
        dir.mkpath(".");
    if (!profileModel->save(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/profiles.json") || !triggerModel->save(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/triggers.json"))
        QMessageBox::critical(this, "Error", "Error saving application settings");
}

void Settings::on_profEdit_clicked(){
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

void Settings::on_profAdd_clicked(){
    ProfileEdit* editwin = new ProfileEdit(profileModel, this);
    if (editwin->exec()){
        Profile profile(editwin->name(), editwin->standby(), editwin->suspend(), editwin->off(), editwin->awake());
        profileModel->append(profile);
    }
    delete editwin;
}

void Settings::on_profRemove_clicked(){
    if (ui->profiles->currentIndex().isValid())
        profileModel->removeRows(ui->profiles->currentIndex().row(), 1);
}

void Settings::on_trigEdit_clicked(){
    QModelIndex curentIndex = ui->triggers->currentIndex();
    if (curentIndex.isValid()){
        TriggerEdit* editwin = new TriggerEdit(profileModel, this);
        editwin->setData(curentIndex.data(TriggerModel::ProfileRole).toPersistentModelIndex(), curentIndex.data(TriggerModel::TimeRole).toTime(), curentIndex.data(TriggerModel::MondayRole).toBool(), curentIndex.data(TriggerModel::TuesdayRole).toBool(), curentIndex.data(TriggerModel::WednesdayRole).toBool(), curentIndex.data(TriggerModel::ThursdayRole).toBool(), curentIndex.data(TriggerModel::FridayRole).toBool(), curentIndex.data(TriggerModel::SaturdayRole).toBool(), curentIndex.data(TriggerModel::SundayRole).toBool());
        if (editwin->exec()){
            triggerModel->setData(curentIndex, editwin->profile(), TriggerModel::ProfileRole);
            triggerModel->setData(curentIndex, editwin->time(), TriggerModel::TimeRole);
            triggerModel->setData(curentIndex, editwin->weekday(0), TriggerModel::MondayRole);
            triggerModel->setData(curentIndex, editwin->weekday(1), TriggerModel::TuesdayRole);
            triggerModel->setData(curentIndex, editwin->weekday(2), TriggerModel::WednesdayRole);
            triggerModel->setData(curentIndex, editwin->weekday(3), TriggerModel::ThursdayRole);
            triggerModel->setData(curentIndex, editwin->weekday(4), TriggerModel::FridayRole);
            triggerModel->setData(curentIndex, editwin->weekday(5), TriggerModel::SaturdayRole);
            triggerModel->setData(curentIndex, editwin->weekday(6), TriggerModel::SundayRole);
        }
    }
}

void Settings::on_trigAdd_clicked(){
    TriggerEdit* editwin = new TriggerEdit(profileModel, this);
    if (editwin->exec()){
        QBitArray weekdays(7);
        weekdays[0] = editwin->weekday(0);
        weekdays[1] = editwin->weekday(1);
        weekdays[2] = editwin->weekday(2);
        weekdays[3] = editwin->weekday(3);
        weekdays[4] = editwin->weekday(4);
        weekdays[5] = editwin->weekday(5);
        weekdays[6] = editwin->weekday(6);
        Trigger trigger(editwin->time(), weekdays, editwin->profile());
        triggerModel->append(trigger);
    }
    delete editwin;
}

void Settings::on_trigRemove_clicked(){
    if (ui->triggers->currentIndex().isValid())
        triggerModel->removeRows(ui->triggers->currentIndex().row(), 1);
}

void Settings::done(int r){
    if (r == QDialog::Accepted){
        if (!triggerModel->valid()){
            QMessageBox::StandardButton button = QMessageBox::warning(this, "Invalid configuration", "Your triggers are refering to nonexistent profiles, if you continue, these triggers will be deleted. Are you sure to continue?", QMessageBox::Yes | QMessageBox::No);
            if (button == QMessageBox::Yes)
                QDialog::done(r);
        } else
            QDialog::done(r);
    } else
        QDialog::done(r);
}
