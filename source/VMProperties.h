#ifndef VMPROPERTIES_H
#define VMPROPERTIES_H

#include <QSettings>

class VMProperties : public QObject
{
    Q_OBJECT
public:
    explicit VMProperties(QString n, QObject *parent = 0);
    ~VMProperties();

    void remove();
    //void clear();
    void clearDrives();
    void clearNetwork();

    QString getRunPath(QString run = "");
    void createWorkingDirectory(QString run = "");
    void createDiskImages(QString run = "");
    void fillCommandLine(QStringList &options, QString run, bool play) const;

public:
    void addScenario(QString name);
    void removeScenario(QString name);
    QStringList getScenarios() const;

    int getDrivesCount() const;
    void setDriveImage(int num, QString path);
    QString getDriveImage(int num) const;

    void setDriveInterface(int num, QString interface);
    QString getDriveInterface(int num) const;

    void setDriveMedia(int num, QString media);
    QString getDriveMedia(int num) const;

    void setDriveOptions(int num, QString options);
    QString getDriveOptions(int num) const;

    void setSimulatorName(QString name);
    QString getSimulatorName() const;
    QString getSimulatorPath() const;

    void setMemory(QString path);
    QString getMemory() const;

    int getVlanCount() const;
    void setNicSettings(int vlan, const QString &nic, const QString &s);
    QStringList getNics(int vlan) const;
    QString getNicSettings(int vlan, const QString &nic) const;

    void setAdditionalOptions(QString options);
    QString getAdditionalOptions() const;

public:
    void setLogFile(QString run, QString fname);
    QString getLogFile(QString run) const;

    void setLogOptions(QString run, QString options);
    QString getLogOptions(QString run) const;

    void setAdditionalRunOptions(QString run, QString options);
    QString getAdditionalRunOptions(QString run) const;

    void setSnapshotsPeriod(QString run, QString period);
    QString getSnapshotsPeriod(QString run);

    //void setSnapshot(QString run, bool val);
    //bool getSnapshot(QString run) const;

private:
    static QString normalizeRunName(QString run);
    static QString getDriveGroup(int num);
    void setDriveKey(int num, QString key, QString value);
    QString getDriveKey(int num, QString key) const;
    void createDiskImage(QString disk, QString newDisk, QString run);

    int getVersion() const;

private:
    //! Stores properties in ini file.
    QSettings *settings;
    //! Set to true when ini file should be deleted.
    bool removeFile;
    //! Name of the configuration.
    QString name;
    //! Directory where configuration is stored.
    QString path;

signals:

public slots:

};

#endif // VMPROPERTIES_H
