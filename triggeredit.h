#ifndef TRIGGEREDIT_H
#define TRIGGEREDIT_H

#include <QDialog>

#include "profilemodel.h"

namespace Ui {
class TriggerEdit;
}

class TriggerEdit : public QDialog
{
    Q_OBJECT

public:
    explicit TriggerEdit(ProfileModel* profiles, QWidget *parent = nullptr);
    void setData(const QPersistentModelIndex& profile, const QTime& time, bool mo, bool tu, bool we, bool th, bool fr, bool sa, bool su);
    QTime time() const;
    bool weekday(uint8_t day) const;
    QModelIndex profile() const;
    ~TriggerEdit() override;

public slots:
    void done(int r) override;

private:
    Ui::TriggerEdit *ui;
};

#endif // TRIGGEREDIT_H
