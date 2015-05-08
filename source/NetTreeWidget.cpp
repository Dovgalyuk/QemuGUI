#include "NetTreeWidget.h"

NetTreeWidget::NetTreeWidget(QWidget *parent) :
    QTreeWidget(parent), vlanCount(0)
{
    //setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequested(QPoint)));

    /*treeMenu        = new QMenu;
    tmAddRootAction = treeMenu->addAction("Add new VLAN");

    connect(tmAddRootAction, SIGNAL(triggered()), this, SLOT(addNewVlan()));


    rootMenu                    = new QMenu;
    rmAddNewConfigurationAction = rootMenu->addAction("Add New Configuration");
    rmRemConfiguration          = rootMenu->addAction("Remove this Configuration");
    rmRemRootAction             = rootMenu->addAction("Remove this VLAN");

    connect(rmAddNewConfigurationAction,    SIGNAL(triggered()), this, SLOT(addNewConf()));
    connect(rmRemConfiguration,             SIGNAL(triggered()), this, SLOT(removeConf()));
    connect(rmRemRootAction,                SIGNAL(triggered()), this, SLOT(removeVlan()));

    netOptionMenu           = new QMenu;
    nomEditNetOptionAction  = netOptionMenu->addAction("Edit options");
    connect(nomEditNetOptionAction, SIGNAL(triggered()), this, SLOT(editOption()));


    setColumnCount(2);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->header()->setStretchLastSection(false);
    this->header()->setResizeMode(0, QHeaderView::ResizeToContents);
    this->header()->setResizeMode(1, QHeaderView::ResizeToContents);
    */
}

void NetTreeWidget::addRoot(const QString& text)
{
    QTreeWidgetItem* root = new QTreeWidgetItem(this);
    root->setText(0, text);
}

/*void NetTreeWidget::contextMenuRequested(QPoint point)
{
    QTreeWidgetItem* item = this->itemAt(point);
    if (!item)
    {
        treeMenu->popup(mapToGlobal(point));
    }
    else if (item->text(0).contains("VLAN"))
    {
        rmAddNewConfigurationAction->setVisible(item->childCount() == 0);
        rmRemConfiguration->setVisible(item->childCount() != 0);
        rootMenu->popup(mapToGlobal(point));
    }
    else
    {
        netOptionMenu->popup(mapToGlobal(point));
    }
}*/

void NetTreeWidget::addVlan()
{
    this->addRoot(QString("VLAN %1").arg(vlanCount++));
}

void NetTreeWidget::addNic()
{
    if (!currentItem() || currentItem()->parent())
        return;

    // find NIC mask
    int mask = QDNetConfiguration::ALLMODE;
    for (int i = 0 ; i < currentItem()->childCount() ; ++i)
        mask &= ~(currentItem()->child(i)->data(0, Qt::UserRole).toInt());

    if (mask)
    {
        QDNetConfiguration dlg("Add new interface", mask, "");
        if (dlg.exec() == QDialog::Accepted)
        {
            QTreeWidgetItem *nic = new QTreeWidgetItem(currentItem());
            int mode = dlg.getCurrentMode();
            nic->setData(0, Qt::UserRole, mode);
            nic->setText(0, dlg.getNic());
            nic->setText(1, dlg.getSettings());
        }

        currentItem()->setExpanded(true);
        this->resizeColumnToContents(0);
        this->resizeColumnToContents(1);
    }
}

void NetTreeWidget::removeItem()
{
    QTreeWidgetItem *item = currentItem();
    if (!item)
        return;

    if (item->parent())
    {
        // NIC
        delete item;
    }
    else
    {
        // vlan
        delete item;

        vlanCount--;
        QList<QTreeWidgetItem*> roots = this->findItems("VLAN", Qt::MatchStartsWith);

        int i = 0;
        foreach(QTreeWidgetItem *root, roots)
            root->setText(0, QString("VLAN %1").arg(i++));
    }

    //emit changeConfiguration();
}

void NetTreeWidget::saveSettings(VMProperties *vm)
{
    QList<QTreeWidgetItem*> roots = this->findItems("VLAN", Qt::MatchStartsWith);
    vm->clearNetwork();
    int vlan = 0;
    foreach(QTreeWidgetItem *root, roots)
    {
        int optionsCount = root->childCount();
        for (int i = 0 ; i < optionsCount ; ++i)
        {
            QTreeWidgetItem *nic = root->child(i);
            vm->setNicSettings(vlan, nic->text(0), nic->text(1));
        }
        ++vlan;
    }
}

void NetTreeWidget::loadSettings(VMProperties *vm)
{
    clear();
    int vlans = vm->getVlanCount();
    for (int vlan = 0 ; vlan < vlans ; ++vlan)
    {
        QTreeWidgetItem *root = new QTreeWidgetItem(this);
        root->setText(0, QString("VLAN %1").arg(vlan));
        QStringList nics = vm->getNics(vlan);
        foreach (QString name, nics)
        {
            QTreeWidgetItem* nic = new QTreeWidgetItem(root);
            int mode = QDNetConfiguration::NICMODE;
            if (name == "tap")
                mode = QDNetConfiguration::TAPMODE;
            else if (name == "user")
                mode = QDNetConfiguration::USERMODE;
            nic->setData(0, Qt::UserRole, mode);
            nic->setText(0, name);
            nic->setText(1, vm->getNicSettings(vlan, name));
        }
    }
}

void NetTreeWidget::editNic()
{
    if (!currentItem() || !currentItem()->parent())
        return;

    QDNetConfiguration dlg("Edit network interface", currentItem()->data(0, Qt::UserRole).toInt(), currentItem()->text(1));
    if (dlg.exec() == QDialog::Accepted)
    {
        currentItem()->setText(1, dlg.getSettings());
    }

    this->resizeColumnToContents(0);
    this->resizeColumnToContents(1);
    /*
    QString currentText = currentItem->text(0);
    int dialogMode = 0;
    if (currentText.contains(QString("nic:")))
        dialogMode = NICMODE;
    else if (currentText.contains(QString("tap:")))
        dialogMode = TAPMODE;
    else if (currentText.contains(QString("user:")))
        dialogMode = USERMODE;

    QDNetConfiguration* configuration = new QDNetConfiguration(currentItem->parent()->text(0), (NetConfigurationMode)dialogMode, currentItem->text(1));
    if (configuration->exec() == QDialog::Accepted)
    {
        if (currentText.contains(QString("nic:")))
            currentItem->setText(1, configuration->getNicSettings());
        else if (currentText.contains(QString("tap:")))
            currentItem->setText(1, configuration->getTapSettings());
        else if (currentText.contains(QString("user:")))
            currentItem->setText(1, configuration->getUserSettings());
    }

    delete configuration;

    this->resizeColumnToContents(0);
    this->resizeColumnToContents(1);

    emit changeConfiguration();*/
}
