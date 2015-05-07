#ifndef REPLAYOPTIONSDIALOG_H
#define REPLAYOPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class ReplayOptionsDialog;
}

class ReplayOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplayOptionsDialog(QWidget *parent = 0);
    ~ReplayOptionsDialog();

    QString getRunName() const;
    QString getSnapshotsPeriod() const;

public Q_SLOTS:
    virtual void accept();

private:
    Ui::ReplayOptionsDialog *ui;
};

#endif // REPLAYOPTIONSDIALOG_H
