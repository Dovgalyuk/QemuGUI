#ifndef VMPROPERTIESDIALOG_H
#define VMPROPERTIESDIALOG_H

#include <QDialog>
#include "VMProperties.h"

namespace Ui {
class VMPropertiesDialog;
}

class VMPropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VMPropertiesDialog(QWidget *parent, VMProperties *props);
    ~VMPropertiesDialog();

private:
    void addDrive(const QString &path, const QString &interface, const QString &media, const QString &options);

    VMProperties *vm;

public Q_SLOTS:
    virtual void accept();

private slots:
    void on_addHddButton_clicked();

    void on_addCdromButton_clicked();

    void on_addFloppyButton_clicked();

    void on_editDriveButton_clicked();

    void on_removeDriveButton_clicked();

private:
    Ui::VMPropertiesDialog *ui;
};

#endif // VMPROPERTIESDIALOG_H
