#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include "profilemodel.h"
#include "triggermodel.h"

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

public slots:
    void done(int r) override;

private slots:
    void on_profEdit_clicked();

    void on_profAdd_clicked();

    void on_profRemove_clicked();

    void on_trigEdit_clicked();

    void on_trigAdd_clicked();

    void on_trigRemove_clicked();

    void on_profiles_doubleClicked(const QModelIndex &index);

    void on_triggers_doubleClicked(const QModelIndex &index);

private:
    Ui::Settings *ui;
    ProfileModel* profileModel;
    TriggerModel* triggerModel;

};

#endif // SETTINGS_H
