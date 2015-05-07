#ifndef DRIVEPROPERTIESDIALOG_H
#define DRIVEPROPERTIESDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class DrivePropertiesDialog;
}

class DrivePropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrivePropertiesDialog(const QString &path, const QString &interface, const QString &media, const QString &options, QWidget *parent = 0);
    ~DrivePropertiesDialog();

    QString getPath() const;
    QString getInterface() const;
    QString getMedia() const;
    QString getOptions() const;

private slots:

private:
    Ui::DrivePropertiesDialog *ui;
};

#endif // DRIVEPROPERTIESDIALOG_H
