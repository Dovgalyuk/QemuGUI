#ifndef NETTAPWIDGET_H
#define NETTAPWIDGET_H

#include <QWidget>
#include "lineeditwithlabel.h"
#include "checkboxwithlabel.h"
#include "netabstractwidget.h"

class NetTapWidget : public NetAbstractWidget
{
    Q_OBJECT
public:
    explicit NetTapWidget(QWidget *parent = 0);
    QString getSettings();
    void setSettings(const QString& settings);
private:
    LineEditWithLabel* id;
    LineEditWithLabel* fd;
    LineEditWithLabel* ifname;
    LineEditWithLabel* name;
    LineEditWithLabel* script;
    LineEditWithLabel* downscript;
    LineEditWithLabel* helper;
    CheckBoxWithLabel* netdev;
};

#endif // NETTAPWIDGET_H
