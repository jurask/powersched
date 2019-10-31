#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include "profilemodel.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings() override;
    void saveSettings();

private slots:
    void on_add_clicked();

    void on_remove_clicked();

    void on_edit_clicked();

private:
    Ui::Settings *ui;
    ProfileModel* profileModel;
};

#endif // SETTINGS_H
