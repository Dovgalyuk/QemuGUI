#include "QEMUGlobalSettings.h"

QEMUGlobalSettings::QEMUGlobalSettings(/*QObject *parent*/) :
    QSettings(QSettings::IniFormat, QSettings::UserScope, "QEMU-GUI", "Options")
{
}

QString QEMUGlobalSettings::getDefaultQEMU() const
{
    return value("defaultQEMUApp").toString();
}

void QEMUGlobalSettings::setDefaultQEMU(QString qemu)
{
    setValue("defaultQEMUApp", qemu);
}


QString QEMUGlobalSettings::getConfigurationsPath() const
{
    return value("configurationsPath").toString();
}

void QEMUGlobalSettings::setConfigurationsPath(QString path)
{
    setValue("configurationsPath", path);
}

void QEMUGlobalSettings::removeSimulators()
{
    remove("simulators");
}

void QEMUGlobalSettings::addSimulator(QString name, QString path)
{
    setValue("simulators/" + name, path);
}

QStringList QEMUGlobalSettings::getSimulatorsList()
{
    beginGroup("simulators");
    QStringList res = childKeys();
    endGroup();
    return res;
}

QString QEMUGlobalSettings::getSimulatorPath(QString name) const
{
    return value("simulators/" + name).toString();
}

