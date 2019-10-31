#ifndef PROFILEEDIT_H
#define PROFILEEDIT_H

#include <QDialog>
#include "profilemodel.h"

namespace Ui {
class ProfileEdit;
}

class ProfileEdit : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileEdit(ProfileModel *model, QWidget *parent = nullptr);
    void setData(const QString& name, uint16_t standby, uint16_t suspend, uint16_t off, bool awake);
    ~ProfileEdit() override;
    QString name() const;
    uint16_t standby() const;
    uint16_t suspend() const;
    uint16_t off() const;
    bool awake() const;

public slots:
    void done(int r) override;

private:
    Ui::ProfileEdit *ui;
    ProfileModel* _model;
    QString originalName;
};

#endif // PROFILEEDIT_H
