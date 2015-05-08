#include "QDNetConfiguration.h"

QDNetConfiguration::QDNetConfiguration(const QString &title, int mode, const QString &widgetSettings, QWidget *parent) :
    QDialog(parent), netNic(NULL), netTap(NULL), netUser(NULL)
{
    modeList = new QComboBox;
    if (mode & NICMODE)
    {
        netNic  = new NetNicWidget;
        netNic->setVisible(false);
        modeList->addItem("NIC", NICMODE);
        if (mode == NICMODE)
            netNic->setSettings(widgetSettings);
    }
    if (mode & TAPMODE)
    {
        netTap  = new NetTapWidget;
        netTap->setVisible(false);
        modeList->addItem("Tap", TAPMODE);
        if (mode == TAPMODE)
            netTap->setSettings(widgetSettings);
    }
    if (mode & USERMODE)
    {
        netUser = new NetUserWidget;
        netUser->setVisible(false);
        modeList->addItem("User", USERMODE);
        if (mode == USERMODE)
            netUser->setSettings(widgetSettings);
    }

    QPushButton *okButton        = new QPushButton("OK");
    QPushButton *cancelButton    = new QPushButton("Cancel");

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(modeList, SIGNAL(currentIndexChanged(int)), this, SLOT(selectMode(int)));

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(modeList);
    if (mode & NICMODE)
        mainLayout->addWidget(netNic);
    if (mode & TAPMODE)
        mainLayout->addWidget(netTap);
    if (mode & USERMODE)
        mainLayout->addWidget(netUser);

    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle(title);
    modeList->setCurrentIndex(0);
    selectMode(0);
}

QDNetConfiguration::NetConfigurationMode QDNetConfiguration::getCurrentMode() const
{
    return (QDNetConfiguration::NetConfigurationMode)modeList->itemData(modeList->currentIndex()).toInt();
}

QString QDNetConfiguration::getSettings() const
{
    switch (getCurrentMode())
    {
    case NICMODE:
        return netNic->getSettings();
    case TAPMODE:
        return netTap->getSettings();
    case USERMODE:
        return netUser->getSettings();
    }
    return "";
}

QString QDNetConfiguration::getNic() const
{
    switch (getCurrentMode())
    {
    case NICMODE:
        return "nic";
    case TAPMODE:
        return "tap";
    case USERMODE:
        return "user";
    }
    return "";
}

void QDNetConfiguration::selectMode(int index)
{
    Q_UNUSED(index);

    int mode = getCurrentMode();
    if (netNic)
        netNic->setVisible(false);
    if (netTap)
        netTap->setVisible(false);
    if (netUser)
        netUser->setVisible(false);
    if (netNic)
        netNic->setVisible(mode == NICMODE);
    if (netTap)
        netTap->setVisible(mode == TAPMODE);
    if (netUser)
        netUser->setVisible(mode == USERMODE);

}
