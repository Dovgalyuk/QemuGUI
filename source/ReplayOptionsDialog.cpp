#include "ReplayOptionsDialog.h"
#include "ui_ReplayOptionsDialog.h"

ReplayOptionsDialog::ReplayOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplayOptionsDialog)
{
    ui->setupUi(this);
}

ReplayOptionsDialog::~ReplayOptionsDialog()
{
    delete ui;
}

QString ReplayOptionsDialog::getRunName() const
{
    return ui->runName->text();
}

QString ReplayOptionsDialog::getSnapshotsPeriod() const
{
    return ui->snapshotsPeriod->text();
}

void ReplayOptionsDialog::accept()
{
    if (!getRunName().isEmpty())
        QDialog::accept();
}
