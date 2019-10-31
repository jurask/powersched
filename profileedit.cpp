#include "profileedit.h"
#include "ui_profileedit.h"

#include <QDoubleValidator>
#include <QMessageBox>

ProfileEdit::ProfileEdit(ProfileModel* model, QWidget *parent) : QDialog(parent), ui(new Ui::ProfileEdit){
    ui->setupUi(this);
    _model = model;
}

ProfileEdit::~ProfileEdit(){
    delete ui;
}

void ProfileEdit::done(int r){
    if (r == QDialog::Accepted){
        if (ui->name->text() == ""){
            QMessageBox::critical(this, "Error", "profile name can't be empty");
            ui->name->setFocus(Qt::OtherFocusReason);
        } else if (_model->contains(ui->name->text()) && ui->name->text() != originalName){
            QMessageBox::critical(this, "Error", "Profile with such name allready exists");
            ui->name->setFocus(Qt::OtherFocusReason);
        } else
            QDialog::done(r);
    } else
        QDialog::done(r);
}

void ProfileEdit::setData(const QString &name, uint16_t standby, uint16_t suspend, uint16_t off, bool awake){
    ui->name->setText(name);
    if (standby == 0)
        ui->standbyNever->setChecked(true);
    else
        ui->standby->setValue(standby);
    if (suspend == 0)
        ui->suspendNever->setChecked(true);
    else
        ui->suspend->setValue(suspend);
    if (off == 0)
        ui->offNever->setChecked(true);
    else
        ui->off->setValue(off);
    ui->awake->setChecked(awake);
    originalName = name;
}

QString ProfileEdit::name() const{
    return ui->name->text();
}

uint16_t ProfileEdit::standby() const{
    if (ui->standbyNever->isChecked())
        return 0;
    else
        return ui->standby->value();
}

uint16_t ProfileEdit::suspend() const{
    if (ui->suspendNever->isChecked())
        return 0;
    else
        return ui->suspend->value();
}

uint16_t ProfileEdit::off() const{
    if (ui->offNever->isChecked())
        return 0;
    else
        return ui->off->value();
}

bool ProfileEdit::awake() const{
    return ui->awake->isChecked();
}
