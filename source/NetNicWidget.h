#ifndef NETNICWIDGET_H
#define NETNICWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QComboBox>
#include <QPushButton>
#include <QStringList>
#include "LineEditWithLabel.h"
#include "NetAbstractWidget.h"
#include "CheckBoxWithLabel.h"

class NetNicWidget : public NetAbstractWidget
{
    Q_OBJECT
public:
    explicit NetNicWidget(QWidget *parent = 0);
    QString getSettings();
    void setSettings(const QString& settings);
private:
    LineEditWithLabel* macAddr;
    LineEditWithLabel* name;
    LineEditWithLabel* addr;
    QComboBox*      model;
    QLabel*         modelLabel;
};

#endif // NETNICWIDGET_H
