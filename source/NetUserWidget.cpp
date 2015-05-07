#include "netuserwidget.h"

NetUserWidget::NetUserWidget(QWidget *parent) :
    NetAbstractWidget(parent)
{
    id          = new LineEditWithLabel("id:");
    name        = new LineEditWithLabel("name:");
    net         = new LineEditWithLabel("net:");
    host        = new LineEditWithLabel("host:");
    hostname    = new LineEditWithLabel("hostname:");
    dhcpstart   = new LineEditWithLabel("dhcpstart:");
    dns         = new LineEditWithLabel("dns:");
    netdev         = new CheckBoxWithLabel("dev:");
    isolate     = new CheckBoxWithLabel("restrict");

    QGridLayout* main = new QGridLayout;
    main->addWidget(netdev,                     0, 1);
    main->addWidget(isolate,                    0, 2);
    main->addWidget(id,                         1, 0, 1, 3);
    main->addWidget(name,                       2, 0);
    main->addWidget(net,                        2, 2);
    main->addWidget(host,                       3, 0);
    main->addWidget(hostname,                   3, 2);
    main->addWidget(dhcpstart,                  4, 0);
    main->addWidget(dns,                        4, 2);

    setLayout(main);
    setTitle("user:");
}


QString NetUserWidget::getSettings()
{
    QString setting;
    if (netdev->isCheked())
        setting += QString("dev=true, ");
    if (isolate->isCheked())
        setting += QString("restrict=true, ");
    if (!id->getText().isEmpty())
        setting += QString("id=") + id->getText() + QString(", ");
    if (!name->getText().isEmpty())
        setting += QString("name=") + name->getText() + QString(", ");
    if (!net->getText().isEmpty())
        setting += QString("net=") + net->getText() + QString(", ");
    if (!host->getText().isEmpty())
        setting += QString("host=") + host->getText() + QString(", ");
    if (!hostname->getText().isEmpty())
        setting += QString("hostname=") + hostname->getText() + QString(", ");
    if (!dhcpstart->getText().isEmpty())
        setting += QString("dhcpstart=") + dhcpstart->getText() + QString(", ");
    if (!dns->getText().isEmpty())
        setting += QString("dns=") + dns->getText();

    if (setting.endsWith(QChar(' ')))
        setting.remove(setting.size() - 2, 2);

    return setting;
}

void NetUserWidget::setSettings(const QString& settings)
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
            else if (pair[0] == QString("net"))
                net->setText(pair[1]);
            else if (pair[0] == QString("host"))
                host->setText(pair[1]);
            else if (pair[0] == QString("hostname"))
                hostname->setText(pair[1]);
            else if (pair[0] == QString("dhcpstart"))
                dhcpstart->setText(pair[1]);
            else if (pair[0] == QString("dns"))
                dns->setText(pair[1]);
            else if (pair[0] == QString("dev"))
                netdev->setChecked(true);
            else if (pair[0] == QString("restrict"))
                isolate->setChecked(true);
        }
    }
}
