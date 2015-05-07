#include "GlobalSettingsDialog.h"
#include "ui_GlobalSettingsDialog.h"
#include "QEMUSettings.h"
#include "QEMUGlobalSettings.h"

GlobalSettingsDialog::GlobalSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlobalSettingsDialog)
{
    ui->setupUi(this);

    ui->configurationsPath->setMode("Directory for storing VM configurations", "dir",
                                    "Select existing directory", QEMUSettings::getStartSearchingPosition());

    // load settings
    QEMUGlobalSettings *settings = QEMUSettings::getGlobalSettings();
    ui->configurationsPath->setPath(settings->getConfigurationsPath());
    QStringList simulators = settings->getSimulatorsList();
    foreach (QString name, simulators)
    {
        addSimulator(name, settings->getSimulatorPath(name));
    }
}

GlobalSettingsDialog::~GlobalSettingsDialog()
{
    delete ui;
}

void GlobalSettingsDialog::on_removeButton_clicked()
{
    int row = ui->simulatorsList->currentRow();
    if (row >= 0)
    {
        ui->simulatorsList->removeRow(row);
    }
}

void GlobalSettingsDialog::addSimulator(QString name, QString path)
{
    if (!name.isEmpty() && !path.isEmpty())
    {
        //ui->simulatorsList->addItem(ui->simulatorName->text());
        //ui->simulatorsList->item(0)->setData(1, ui->simulatorPath->text());
        int row = ui->simulatorsList->rowCount();
        ui->simulatorsList->insertRow(row);
        ui->simulatorsList->setItem(row, 0, new QTableWidgetItem(name));
        ui->simulatorsList->setItem(row, 1, new QTableWidgetItem(path));
    }
}

void GlobalSettingsDialog::on_addButton_clicked()
{
    QString name = ui->simulatorName->text();
    QString path = ui->simulatorPath->text();
    // TODO: check duplicates
    addSimulator(name, path);
}

void GlobalSettingsDialog::on_browseButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Select QEMU executable",
                                                QEMUSettings::getQEMUAppStartSearchingPosition());
    if (!file.isEmpty())
        ui->simulatorPath->setText(file);

}

void GlobalSettingsDialog::on_buttonBox_accepted()
{
    // save settings
    QEMUGlobalSettings *settings = QEMUSettings::getGlobalSettings();
    settings->setConfigurationsPath(ui->configurationsPath->getPath());
    settings->removeSimulators();
    int rows = ui->simulatorsList->rowCount();
    for (int i = 0 ; i < rows ; ++i)
    {
        settings->addSimulator(ui->simulatorsList->item(i, 0)->text(),
                               ui->simulatorsList->item(i, 1)->text());
    }
}
