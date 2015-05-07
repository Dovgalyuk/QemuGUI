#include "QEMUSettings.h"

QString QEMUSettings::getStartSearchingPosition()
{
#ifdef Q_OS_WIN32
    return "";
#else
    return "/home";
#endif
}

QString QEMUSettings::getQEMUAppStartSearchingPosition()
{
#ifdef Q_OS_WIN32
    return "c:";
#else
    return "/usr";
#endif
}

QSettings* QEMUSettings::getConfigurationList()
{
   return new QSettings(QSettings::IniFormat, QSettings::UserScope, "QEMU-GUI", "Configurations");
}

QEMUGlobalSettings* QEMUSettings::getGlobalSettings()
{
    static QEMUGlobalSettings settings;
    return &settings;
}

QString QEMUSettings::getQEMUAppPath()
{
    return getGlobalSettings()->getDefaultQEMU();
}


QString QEMUSettings::getVlanCountOption()
{
    return "net/vlan_count";
}
