#include "triggeredit.h"
#include "ui_triggeredit.h"

#include <QMessageBox>

TriggerEdit::TriggerEdit(ProfileModel* profiles, QWidget *parent) : QDialog(parent), ui(new Ui::TriggerEdit){
    ui->setupUi(this);
    ui->profile->setModel(profiles);
}

TriggerEdit::~TriggerEdit(){
    delete ui;
}

void TriggerEdit::done(int r){
    if (r == QDialog::Accepted){
        if (!ui->profile->model()->index(ui->profile->currentIndex(), 0).isValid()){
            QMessageBox::critical(this, "Error", "No valid profile selected");
            ui->profile->setFocus(Qt::OtherFocusReason);
        } else if (!ui->monday->isChecked() && !ui->tuesday->isChecked() && !ui->wednesday->isChecked() && !ui->thursday->isChecked() && !ui->friday->isChecked() && !ui->saturday->isChecked() && !ui->sunday->isChecked()){
            QMessageBox::critical(this, "Error", "No day selected");
        } else
            QDialog::done(r);
    } else
        QDialog::done(r);
}

void TriggerEdit::setData(const QPersistentModelIndex &profile, const QTime &time, bool mo, bool tu, bool we, bool th, bool fr, bool sa, bool su){
    ui->profile->setCurrentIndex(profile.row());
    ui->time->setTime(time);
    ui->monday->setChecked(mo);
    ui->tuesday->setChecked(tu);
    ui->wednesday->setChecked(we);
    ui->thursday->setChecked(th);
    ui->friday->setChecked(fr);
    ui->saturday->setChecked(sa);
    ui->sunday->setChecked(su);
}

QTime TriggerEdit::time() const{
    return ui->time->time();
}

bool TriggerEdit::weekday(uint8_t day) const{
    switch (day){
        case 0:
            return ui->monday->isChecked();
        case 1:
            return ui->tuesday->isChecked();
        case 2:
            return ui->wednesday->isChecked();
        case 3:
            return ui->thursday->isChecked();
        case 4:
            return ui->friday->isChecked();
        case 5:
            return ui->saturday->isChecked();
        default:
            return ui->sunday->isChecked();
    }
}

QModelIndex TriggerEdit::profile() const{
    return ui->profile->model()->index(ui->profile->currentIndex(), 0);
}
