#ifndef NETABSTRACTWIDGET_H
#define NETABSTRACTWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QStringList>
#include <QMessageBox>
#include "checkboxwithlabel.h"
#include <QSettings>

class NetAbstractWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit NetAbstractWidget(QWidget *parent = 0);
    virtual QString getSettings() = 0;
    virtual void setSettings(const QString& settings) = 0;
protected:
    //void insertWidgetIntoLayout(QBoxLayout* layout, QWidget* firstWidget, QWidget* secondWidget);
    //void insertLayoutIntoLayout(QBoxLayout* mainlayout, QVector<QBoxLayout*>& layouts);
    //void insertOptionIntoString(QString& base, QString optionName, QString optionValue);
    QStringList getSettingsList(const QString& settings);
};

#endif // NETABSTRACTWIDGET_H
