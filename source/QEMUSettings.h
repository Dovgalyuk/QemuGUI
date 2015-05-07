#ifndef QEMUSETTINGS_H
#define QEMUSETTINGS_H

#include <QString>
#include <QSettings>

#include "QEMUGlobalSettings.h"
#include "VMProperties.h"

namespace QEMUSettings
{
    QString     getStartSearchingPosition();
    QString     getQEMUAppStartSearchingPosition();
    QString     getQEMUAppPath();

    QSettings*  getConfigurationList();
    QEMUGlobalSettings*  getGlobalSettings();

    QString     getVlanCountOption();
}

#endif // QEMUSETTINGS_H
