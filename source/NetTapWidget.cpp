#include "NetTapWidget.h"

NetTapWidget::NetTapWidget(QWidget *parent) :
    NetAbstractWidget(parent)
{
    id          = new LineEditWithLabel("id:");
    fd          = new LineEditWithLabel("fd:");
    name        = new LineEditWithLabel("name:");
    ifname       = new LineEditWithLabel("ifname:");
    script      = new LineEditWithLabel("script:");
    downscript  = new LineEditWithLabel("downscript:");
    helper      = new LineEditWithLabel("helper:");
    netdev      = new CheckBoxWithLabel("dev:");

    QGridLayout* main = new QGridLayout;
    main->addWidget(netdev,         0, 1);
    main->addWidget(name,           1, 0);
    main->addWidget(ifname,         1, 1);
    main->addWidget(script,         2, 0);
    main->addWidget(downscript,     2, 1);
    main->addWidget(helper,         3, 0, 1, 2);

    setLayout(main);
    setTitle("tap:");
}


QString NetTapWidget::getSettings()
{
    QString setting;
    if (netdev->isCheked())
        setting += QString("dev=true, ");
    if (!id->getText().isEmpty())
        setting += QString("id=") + id->getText() + QString(", ");
    if (!fd->getText().isEmpty())
        setting += QString("fd=") + fd->getText() + QString(", ");
    if (!name->getText().isEmpty())
        setting += QString("name=") + name->getText() + QString(", ");
    if (!ifname->getText().isEmpty())
        setting += QString("ifname=") + ifname->getText() + QString(", ");
    if (!script->getText().isEmpty())
        setting += QString("script=") + script->getText() + QString(", ");
    if (!downscript->getText().isEmpty())
        setting += QString("downscript=") + downscript->getText() + QString(", ");
    if (!helper->getText().isEmpty())
        setting += QString("helper=") + helper->getText();

    if (setting.endsWith(QChar(' ')))
        setting.remove(setting.size() - 2, 2);

    return setting;
}

void NetTapWidget::setSettings(const QString& settings)
{
    QStringList settingsList = this->getSettingsList(settings);
    foreach (QString setting, settingsList)
    {
        QStringList pair = setting.split("=");
        if (pair.size() == 2)
        {
            if (pair[0] == QString("name"))
                name->setText(pair[1]);
            else if (pair[0] == QString("id"))
                id->setText(pair[1]);
            else if (pair[0] == QString("fd"))
                fd->setText(pair[1]);
            else if (pair[0] == QString("ifname"))
                ifname->setText(pair[1]);
            else if (pair[0] == QString("script"))
                script->setText(pair[1]);
            else if (pair[0] == QString("downscript"))
                downscript->setText(pair[1]);
            else if (pair[0] == QString("helper"))
                helper->setText(pair[1]);
            else if (pair[0] == QString("dev"))
                netdev->setChecked(true);
        }
    }
}
