#ifndef QDNETCONFIGURATION_H
#define QDNETCONFIGURATION_H

#include <QDialog>
#include <QLayout>
#include <QPushButton>
#include "netnicwidget.h"
#include "nettapwidget.h"
#include "netuserwidget.h"

class QDNetConfiguration : public QDialog
{
    Q_OBJECT
public:
    enum NetConfigurationMode
    {
        NICMODE  = 1 << 0,
        TAPMODE  = 1 << 1,
        USERMODE = 1 << 2,
        ALLMODE = NICMODE | TAPMODE | USERMODE
    };

public:
    explicit QDNetConfiguration(const QString& title, int mode, const QString &widgetSettings, QWidget *parent = 0);

    NetConfigurationMode getCurrentMode() const;
    QString getSettings() const;
    QString getNic() const;
private:
    NetNicWidget *netNic;
    NetTapWidget *netTap;
    NetUserWidget *netUser;
    //QPushButton *okButton;
    //QPushButton *cancelButton;
    QComboBox *modeList;
    QVBoxLayout *mainLayout;
signals:

private slots:
    void selectMode(int index);
};

#endif // QDNETCONFIGURATION_H
