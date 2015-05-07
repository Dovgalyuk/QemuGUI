#include "DrivePropertiesDialog.h"
#include "ui_DrivePropertiesDialog.h"
#include "QEMUSettings.h"

DrivePropertiesDialog::DrivePropertiesDialog(const QString &path, const QString &interface, const QString &media, const QString &options, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrivePropertiesDialog)
{
    ui->setupUi(this);

    ui->filePath->setMode("Disk image path", "file", "Select disk image file",
                          QEMUSettings::getStartSearchingPosition(),
                          "Image files (*.img *.raw *.iso *.cloop *.cow *.qcow *.qcow2 *.vmdk *.vdl)");

    ui->interfaceCombo->addItem("ide");
    ui->interfaceCombo->addItem("scsi");
    ui->interfaceCombo->addItem("sd");
    ui->interfaceCombo->addItem("mtd");
    ui->interfaceCombo->addItem("floppy");
    ui->interfaceCombo->addItem("pflash");
    ui->interfaceCombo->addItem("virtio");

    ui->mediaCombo->addItem("disk");
    ui->mediaCombo->addItem("cdrom");

    ui->filePath->setPath(path);
    ui->interfaceCombo->setCurrentIndex(ui->interfaceCombo->findText(interface));
    ui->mediaCombo->setCurrentIndex(ui->mediaCombo->findText(media));
    ui->optionsEdit->setText(options);
}

DrivePropertiesDialog::~DrivePropertiesDialog()
{
    delete ui;
}

QString DrivePropertiesDialog::getPath() const
{
    return ui->filePath->getPath();
}

QString DrivePropertiesDialog::getInterface() const
{
    return ui->interfaceCombo->currentText();
}

QString DrivePropertiesDialog::getMedia() const
{
    return ui->mediaCombo->currentText();
}

QString DrivePropertiesDialog::getOptions() const
{
    return ui->optionsEdit->text();
}
