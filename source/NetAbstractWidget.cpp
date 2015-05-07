#include "netabstractwidget.h"

NetAbstractWidget::NetAbstractWidget(QWidget *parent) :
    QGroupBox(parent)
{
}

/*void NetAbstractWidget::insertWidgetIntoLayout(QBoxLayout* layout, QWidget* firstWidget, QWidget* secondWidget)
{
    layout->addWidget(firstWidget);
    layout->addWidget(secondWidget);
}*/

/*void NetAbstractWidget::insertLayoutIntoLayout(QBoxLayout* mainlayout, QVector<QBoxLayout*>& layouts)
{
    foreach (QBoxLayout* layout, layouts)
        mainlayout->addLayout(layout);
}*/

/*void NetAbstractWidget::insertOptionIntoString(QString& base, QString optionName, QString optionValue)
{
    base += optionName + optionValue + QString(",");
}*/

QStringList NetAbstractWidget::getSettingsList(const QString& settings)
{
    QStringList settingsList = settings.split(QString(", "));
    return settingsList;
}

