#include "VMPropertiesDialog.h"
#include "ui_VMPropertiesDialog.h"
#include "QEMUSettings.h"
#include "DrivePropertiesDialog.h"

VMPropertiesDialog::VMPropertiesDialog(QWidget *parent, VMProperties *props) :
    QDialog(parent), vm(props),
    ui(new Ui::VMPropertiesDialog)
{
    ui->setupUi(this);

    connect(ui->addVLANButton,   SIGNAL(clicked()), ui->netTreeWidget, SLOT(addVlan()));
    connect(ui->addNICButton,    SIGNAL(clicked()), ui->netTreeWidget, SLOT(addNic()));
    connect(ui->editNICButton,   SIGNAL(clicked()), ui->netTreeWidget, SLOT(editNic()));
    connect(ui->removeNetButton, SIGNAL(clicked()), ui->netTreeWidget, SLOT(removeItem()));

    // load simulators list
    QStringList simulators = QEMUSettings::getGlobalSettings()->getSimulatorsList();
    ui->simulatorsList->addItems(simulators);

    // drives
    int drivesCount = vm->getDrivesCount();
    for (int i = 0 ; i < drivesCount ; ++i)
    {
        addDrive(vm->getDriveImage(i), vm->getDriveInterface(i),
                 vm->getDriveMedia(i), vm->getDriveOptions(i));
    }

    // common
    ui->simulatorsList->setCurrentIndex(ui->simulatorsList->findText(vm->getSimulatorName()));
    ui->memoryLineEdit->setText(vm->getMemory());

    // additional options
    ui->additionalOptions->setPlainText(vm->getAdditionalOptions());

    if (!vm->getScenarios().empty())
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    // network
    ui->netTreeWidget->loadSettings(vm);
}

VMPropertiesDialog::~VMPropertiesDialog()
{
    delete ui;
}

void VMPropertiesDialog::addDrive(const QString &path, const QString &interface, const QString &media, const QString &options)
{
    int row = ui->drivesTable->rowCount();
    ui->drivesTable->insertRow(row);
    ui->drivesTable->setItem(row, 0, new QTableWidgetItem(path));
    ui->drivesTable->setItem(row, 1, new QTableWidgetItem(interface));
    ui->drivesTable->setItem(row, 2, new QTableWidgetItem(media));
    ui->drivesTable->setItem(row, 3, new QTableWidgetItem(options));
}

void VMPropertiesDialog::accept()
{
    // drives
    vm->clearDrives();
    int drivesCount = ui->drivesTable->rowCount();
    for (int i = 0 ; i < drivesCount ; ++i)
    {
        vm->setDriveImage(i, ui->drivesTable->item(i, 0)->text());
        vm->setDriveInterface(i, ui->drivesTable->item(i, 1)->text());
        vm->setDriveMedia(i, ui->drivesTable->item(i, 2)->text());
        vm->setDriveOptions(i, ui->drivesTable->item(i, 3)->text());
    }

    // common
    vm->setSimulatorName(ui->simulatorsList->currentText());
    vm->setMemory(ui->memoryLineEdit->text());
    // net
    ui->netTreeWidget->saveSettings(vm);

    // additionalCommands
    vm->setAdditionalOptions(ui->additionalOptions->toPlainText().replace("\n", " "));

    QDialog::accept();
}


void VMPropertiesDialog::on_addHddButton_clicked()
{
    DrivePropertiesDialog dlg("", "ide", "disk", "");
    if (dlg.exec() == QDialog::Accepted)
    {
        addDrive(dlg.getPath(), dlg.getInterface(), dlg.getMedia(), dlg.getOptions());
    }
}

void VMPropertiesDialog::on_addCdromButton_clicked()
{
    DrivePropertiesDialog dlg("", "ide", "cdrom", "");
    if (dlg.exec() == QDialog::Accepted)
    {
        addDrive(dlg.getPath(), dlg.getInterface(), dlg.getMedia(), dlg.getOptions());
    }
}

void VMPropertiesDialog::on_addFloppyButton_clicked()
{
    DrivePropertiesDialog dlg("", "floppy", "disk", "");
    if (dlg.exec() == QDialog::Accepted)
    {
        addDrive(dlg.getPath(), dlg.getInterface(), dlg.getMedia(), dlg.getOptions());
    }
}

void VMPropertiesDialog::on_editDriveButton_clicked()
{
    int row = ui->drivesTable->currentRow();
    if (row < 0 || row >= ui->drivesTable->rowCount())
        return;

    DrivePropertiesDialog dlg(ui->drivesTable->item(row, 0)->text(),
                              ui->drivesTable->item(row, 1)->text(),
                              ui->drivesTable->item(row, 2)->text(),
                              ui->drivesTable->item(row, 3)->text());
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->drivesTable->item(row, 0)->setText(dlg.getPath());
        ui->drivesTable->item(row, 1)->setText(dlg.getInterface());
        ui->drivesTable->item(row, 2)->setText(dlg.getMedia());
        ui->drivesTable->item(row, 3)->setText(dlg.getOptions());
    }

}

void VMPropertiesDialog::on_removeDriveButton_clicked()
{
    int row = ui->drivesTable->currentRow();
    if (row >= 0)
        ui->drivesTable->removeRow(row);
}
