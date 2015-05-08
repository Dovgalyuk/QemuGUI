#include "NetNicWidget.h"

NetNicWidget::NetNicWidget(QWidget *parent) :
    NetAbstractWidget(parent)
{

    macAddr                 = new LineEditWithLabel("macaddr:");
    name                    = new LineEditWithLabel("name:");
    addr                    = new LineEditWithLabel("address:");
    modelLabel              = new QLabel("model:");
    model                   = new QComboBox;

    // TODO: Перенести список карточек в одно место!
    QStringList devices;

    devices << "none" << "virtio" << "i82551" << "i82557b"
            << "i82559er" << "ne2k_pci" << "ne2k_isa"
            << "pcnet" << "rtl8139" << "e1000"
            << "smc91c111" << "lance" << "mcf_fec";

    model->insertItems(0, devices);


    QHBoxLayout* modelLayout    = new QHBoxLayout;
    modelLayout->addWidget(modelLabel);
    modelLayout->addWidget(model);
    modelLayout->setSpacing(0);

    QGridLayout* main = new QGridLayout;
    main->addWidget(name,           1, 0);
    main->addLayout(modelLayout,    1, 2);
    main->addWidget(macAddr,        2, 0);
    main->addWidget(addr,           2, 2);

    setLayout(main);
    setTitle("nic:");
}

QString NetNicWidget::getSettings()
{
    QString setting;
    if (!name->getText().isEmpty())
        setting += QString("name=") + name->getText() + QString(", ");
    if (model->currentText() != QString("none"))
        setting += QString("model=") + model->currentText() + QString(", ");
    if (!macAddr->getText().isEmpty())
        setting += QString("macaddr=") + macAddr->getText() + QString(", ");
    if (!addr->getText().isEmpty())
        setting += QString("addr=") + addr->getText();

    if (setting.endsWith(QChar(' ')))
        setting.remove(setting.size() - 2, 2);

    return setting;
}

void NetNicWidget::setSettings(const QString& settings)
{
    QStringList settingsList = this->getSettingsList(settings);
    foreach (QString setting, settingsList)
    {
        QStringList pair = setting.split("=");
        if (pair.size() == 2)
        {
            if (pair[0] == QString("name"))
                name->setText(pair[1]);
            else if (pair[0] == QString("macaddr"))
                macAddr->setText(pair[1]);
            else if (pair[0] == QString("addr"))
                addr->setText(pair[1]);
            else if (pair[0] == QString("model"))
                model->setItemText(model->currentIndex(), pair[1]);
        }
    }
}
