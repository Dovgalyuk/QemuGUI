#ifndef QEMUGLOBALSETTINGS_H
#define QEMUGLOBALSETTINGS_H

#include <QSettings>
#include <QStringList>

class QEMUGlobalSettings : protected QSettings
{
    Q_OBJECT
public:
    explicit QEMUGlobalSettings(/*QObject *parent = 0*/);

    QString getDefaultQEMU() const;
    void setDefaultQEMU(QString qemu);

    QString getConfigurationsPath() const;
    void setConfigurationsPath(QString path);

    void removeSimulators();
    void addSimulator(QString name, QString path);
    QStringList getSimulatorsList();
    QString getSimulatorPath(QString name) const;

signals:

public slots:

};

#endif // QEMUGLOBALSETTINGS_H
