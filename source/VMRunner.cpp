#include <QProcess>

#include "VMRunner.h"

VMRunner::VMRunner(VMProperties *v, const QStringList &opt, QObject *parent) :
    QThread(parent), vm(v), options(opt)
{
}

void VMRunner::run()
{
    QProcess process;
    process.execute(vm->getSimulatorPath(), options);

#ifdef Q_OS_WIN32
    /*QFile errors(this->getQEMUPath() + "stderr.txt");
    if (errors.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString errorText = errors.readAll();
        if (!errorText.isEmpty())
            QMessageBox::critical(this, "Error:", errorText);
    }*/
#endif

    QString errorText(process.readAllStandardError().data());
    QString stdoutText(process.readAllStandardOutput().data());
    emit resultReady(errorText, stdoutText);
}
