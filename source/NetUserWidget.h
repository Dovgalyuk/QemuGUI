#ifndef NETUSERWIDGET_H
#define NETUSERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "lineeditwithlabel.h"
#include "checkboxwithlabel.h"
#include "netabstractwidget.h"

class NetUserWidget : public NetAbstractWidget
{
    Q_OBJECT
public:
    explicit NetUserWidget(QWidget *parent = 0);
    void getOptions(QStringList& cmdList);
    void saveSettings(QSettings& settings, const QString& section);
    void loadSettings(QSettings& settings, const QString& section);
    QString getSettings();
    void setSettings(const QString& settings);
private:
    LineEditWithLabel*  id;
    LineEditWithLabel*  name;
    LineEditWithLabel*  net;
    LineEditWithLabel*  host;
    LineEditWithLabel*  hostname;
    LineEditWithLabel*  dhcpstart;
    LineEditWithLabel*  dns;
    CheckBoxWithLabel*  netdev;
    CheckBoxWithLabel*  isolate;
};

#endif // NETUSERWIDGET_H
