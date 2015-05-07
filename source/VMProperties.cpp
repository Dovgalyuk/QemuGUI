#include <QDir>
#include <QFile>
#include <QProcess>
#include <QStringList>
#include <QDateTime>

#include "VMProperties.h"
#include "QEMUSettings.h"

static const QString defaultRunName = "::";
const int CURRENT_VERSION = 2;

VMProperties::VMProperties(QString n, QObject *parent)
    : QObject(parent), name(n), settings(NULL), removeFile(false)
{
    path = QEMUSettings::getGlobalSettings()->getConfigurationsPath();
    if (!path.isEmpty() && !path.endsWith('/') && !path.endsWith('\\'))
        path += '/';
    settings = new QSettings(path + "VM_" + name + ".ini", QSettings::IniFormat);

    // version will be used later when format changes
    if (!settings->contains("version"))
        settings->setValue("version", CURRENT_VERSION);
}

VMProperties::~VMProperties()
{
    QString path = settings->fileName();
    delete settings;
    if (removeFile)
    {
        QFile::remove(path);
    }
}

void VMProperties::remove()
{
    removeFile = true;
}

void VMProperties::clearDrives()
{
    settings->remove("drives");
}

void VMProperties::clearNetwork()
{
    settings->remove("network");
}

/*void VMProperties::clear()
{
    settings->clear();
    settings->setValue("version", CURRENT_VERSION);
}*/

QString VMProperties::getRunPath(QString run)
{
    QString result = path + name + "/" + run;
    if (!run.isEmpty())
        result += "/";
    return result;
}

void VMProperties::createWorkingDirectory(QString run)
{
    QDir().mkpath(getRunPath(run));
}

void VMProperties::createDiskImages(QString run)
{
    int drivesCount = getDrivesCount();
    for (int i = 0 ; i < drivesCount ; ++i)
    {
        createDiskImage(getDriveImage(i), QString("hd%1.qcow").arg((char)('a' + i)), run);
    }
}

void VMProperties::fillCommandLine(QStringList &options, QString run, bool play) const
{
    bool isRetrace = !run.isEmpty();
    // drives
    int drivesCount = getDrivesCount();
    for (int i = 0 ; i < drivesCount ; ++i)
    {
        options << "-drive";

        QString params;
        QString path = getDriveImage(i);
        params = "file=" + (isRetrace ? QString("hd%1.qcow").arg((char)('a' + i)) : path);
        QString interface = getDriveInterface(i);
        if (!interface.isEmpty())
            params += QString(",if=") + interface;
        QString media = getDriveMedia(i);
        if (!media.isEmpty())
            params += QString(",media=") + media;
        QString opt = getDriveOptions(i);
        if (!opt.isEmpty())
            params += QString(",") + opt;

        options << params;
    }

    // m (memory)
    if (!getMemory().isEmpty())
        options << "-m" << getMemory();

    // netTree
    int vlans = getVlanCount();
    for (int vlan = 0 ; vlan < vlans ; ++vlan)
    {
        QStringList nics = getNics(vlan);
        foreach (QString name, nics)
        {
            QString opt;
            if (play && name != "nic" && name != "dump")
            {
                opt = QString("retrace,vlan=%1").arg(vlan);
            }
            else
            {
                opt = name + QString(",vlan=%1").arg(vlan);
                QString s = getNicSettings(vlan, name).remove(' ');
                if (!s.isEmpty())
                    opt += QString(",") + s;
            }
            options << "-net" << opt;
        }
    }

    // log
    if (!getLogFile(run).isEmpty() && !getLogOptions(run).isEmpty())
        options << "-D" << getLogFile(run) << "-d" << getLogOptions(run);

    // additional options
    QStringList additionalOptions = getAdditionalOptions().split(" ");
    if (!additionalOptions.front().isEmpty())
        foreach (QString command, additionalOptions)
            options << command;
    additionalOptions = getAdditionalRunOptions(run).split(" ");
    if (!additionalOptions.front().isEmpty())
        foreach (QString command, additionalOptions)
            options << command;
}

void VMProperties::addScenario(QString name)
{
    name = normalizeRunName(name);
    settings->beginGroup("runs");
    // need at least one attribute to save the run name
    settings->setValue(name + "/datetime", QDateTime::currentDateTime().toString(Qt::ISODate));
    settings->setValue(name + "/log/file", settings->value(defaultRunName + "/log/file"));
    settings->setValue(name + "/log/options", settings->value(defaultRunName + "/log/options"));
    settings->setValue(name + "/additional", settings->value(defaultRunName + "/additional"));
    settings->endGroup();
}

void VMProperties::removeScenario(QString name)
{
    settings->remove("runs/" + normalizeRunName(name));
}

QStringList VMProperties::getScenarios() const
{
    settings->beginGroup("runs");
    QStringList res = settings->childGroups();
    settings->endGroup();
    res.removeOne(defaultRunName);
    return res;
}

int VMProperties::getDrivesCount() const
{
    settings->beginGroup("drives");
    int res = settings->childGroups().size();
    settings->endGroup();
    return res;
}

void VMProperties::setDriveImage(int num, QString path)
{
    setDriveKey(num, "file", path);
}

QString VMProperties::getDriveImage(int num) const
{
    return getDriveKey(num, "file");
}

void VMProperties::setDriveInterface(int num, QString interface)
{
    setDriveKey(num, "interface", interface);
}

QString VMProperties::getDriveInterface(int num) const
{
    return getDriveKey(num, "interface");
}

void VMProperties::setDriveMedia(int num, QString media)
{
    setDriveKey(num, "media", media);
}

QString VMProperties::getDriveMedia(int num) const
{
    return getDriveKey(num, "media");
}

void VMProperties::setDriveOptions(int num, QString options)
{
    setDriveKey(num, "options", options);
}

QString VMProperties::getDriveOptions(int num) const
{
    return getDriveKey(num, "options");
}

void VMProperties::setSimulatorName(QString name)
{
    settings->setValue("common/simulator", name);
}

QString VMProperties::getSimulatorName() const
{
    return settings->value("common/simulator").toString();
}

QString VMProperties::getSimulatorPath() const
{
    return QEMUSettings::getGlobalSettings()->getSimulatorPath(getSimulatorName());
}

void VMProperties::setMemory(QString path)
{
    settings->setValue("common/memory", path);
}

QString VMProperties::getMemory() const
{
    return settings->value("common/memory").toString();
}

int VMProperties::getVlanCount() const
{
    settings->beginGroup("network");
    int res = settings->childGroups().size();
    settings->endGroup();
    return res;
}

void VMProperties::setNicSettings(int vlan, const QString &nic, const QString &s)
{
    settings->setValue(QString("network/%1/").arg(vlan) + nic, s);
}

QStringList VMProperties::getNics(int vlan) const
{
    settings->beginGroup(QString("network/%1").arg(vlan));
    QStringList res = settings->childKeys();
    settings->endGroup();
    return res;
}

QString VMProperties::getNicSettings(int vlan, const QString &nic) const
{
    return settings->value(QString("network/%1/").arg(vlan) + nic).toString();
}

void VMProperties::setAdditionalOptions(QString options)
{
    settings->setValue("common/additional", options);
}

QString VMProperties::getAdditionalOptions() const
{
    return settings->value("common/additional").toString();
}

/* Run parameters */

void VMProperties::setLogFile(QString run, QString fname)
{
    settings->setValue("runs/" + normalizeRunName(run) + "/log/file", fname);
}

QString VMProperties::getLogFile(QString run) const
{
    return settings->value("runs/" + normalizeRunName(run) + "/log/file").toString();
}

void VMProperties::setLogOptions(QString run, QString options)
{
    settings->setValue("runs/" + normalizeRunName(run) + "/log/options", options);
}

QString VMProperties::getLogOptions(QString run) const
{
    return settings->value("runs/" + normalizeRunName(run) + "/log/options").toString();
}

void VMProperties::setAdditionalRunOptions(QString run, QString options)
{
    settings->setValue("runs/" + normalizeRunName(run) + "/additional", options);
}

QString VMProperties::getAdditionalRunOptions(QString run) const
{
    return settings->value("runs/" + normalizeRunName(run) + "/additional").toString();
}

void VMProperties::setSnapshotsPeriod(QString run, QString period)
{
    settings->setValue("runs/" + normalizeRunName(run) + "/period", period);
}

QString VMProperties::getSnapshotsPeriod(QString run)
{
    return settings->value("runs/" + normalizeRunName(run) + "/period").toString();
}

/*void VMProperties::setSnapshot(QString run, bool val)
{
    settings->setValue("runs/" + normalizeRunName(run) + "/snapshot", val);
}

bool VMProperties::getSnapshot(QString run) const
{
    return settings->value("runs/" + normalizeRunName(run) + "/snapshot").toBool();
}*/

QString VMProperties::normalizeRunName(QString run)
{
    run.replace(QRegExp("[\\ \\\\/\\*\\?\\.\\:]"), "_");
    if (run.isEmpty())
        run = defaultRunName;

    return run;
}

QString VMProperties::getDriveGroup(int num)
{
    return QString("drives/%1").arg(num);
}

void VMProperties::setDriveKey(int num, QString key, QString value)
{
    settings->setValue(getDriveGroup(num) + "/" + key, value);
}

QString VMProperties::getDriveKey(int num, QString key) const
{
    return settings->value(getDriveGroup(num) + "/" + key).toString();
}

void VMProperties::createDiskImage(QString disk, QString newDisk, QString run)
{
    if (disk.isEmpty())
        return;

    QString newDiskPath = getRunPath(run) + newDisk;
    QString imgPath = QString(QFileInfo(getSimulatorPath()).absolutePath() + "/qemu-img.exe");
    QProcess img;
    QStringList options;
    options << "create" << "-f" << "qcow2" << "-b" << disk << newDiskPath;
    img.execute(imgPath, options);
}

int VMProperties::getVersion() const
{
    return settings->value("version").toInt();
}

