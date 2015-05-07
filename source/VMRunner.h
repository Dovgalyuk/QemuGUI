#ifndef VMRUNNER_H
#define VMRUNNER_H

#include <QThread>
#include <QString>
#include <QStringList>

#include "VMProperties.h"

class VMRunner : public QThread
{
    Q_OBJECT
public:
    explicit VMRunner(VMProperties *v, const QStringList &opt, QObject *parent = 0);

    virtual void run();
private:
    VMProperties *vm;
    QStringList options;
signals:
    void resultReady(const QString &err, const QString &out);

public slots:

};

#endif // VMRUNNER_H
