#include "ConfTreeWidget.h"
#include "ReplayOptionsDialog.h"

ConfTreeWidget::ConfTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    /*
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequested(QPoint)));

    baseMenu = new QMenu;
    bmAddNewConfiguration = baseMenu->addAction("Add new configuration");

    connect(bmAddNewConfiguration, SIGNAL(triggered()), this, SLOT(addNewConf()));

    confMenu = new QMenu;
    //cfmAddNewScenarioAction                 = confMenu->addAction("Add scenario");
    //confMenu->addSeparator();
    cfmRenameConfigurationAction            = confMenu->addAction("Rename configuration");
    cfmRemoveConfigurationAction            = confMenu->addAction("Remove configuration");

    scenarioMenu = new QMenu;
    scmRenameScenarioAction = scenarioMenu->addAction("Rename scenario");
    scmRemoveScenarioAction = scenarioMenu->addAction("Remove scenario");

    connect(scmRenameScenarioAction, SIGNAL(triggered()), this, SLOT(renameScenario()));

    connect(this->itemDelegate(), SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)), this, SLOT(checkRenamedItem(QWidget*, QAbstractItemDelegate::EndEditHint)));
*/
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->header()->setStretchLastSection(false);
    this->header()->setResizeMode(0, QHeaderView::ResizeToContents);
}

/*void ConfTreeWidget::contextMenuRequested(QPoint point)
{
    QTreeWidgetItem* item = this->itemAt(point);
    if (!item)
        baseMenu->popup(mapToGlobal(point));
    else if (item->parent() == NULL)
        confMenu->popup(mapToGlobal(point));
    else
        scenarioMenu->popup(mapToGlobal(point));
}*/

void ConfTreeWidget::addNewConf()
{
    QDSetName dialog("Configuration name:");

    if (dialog.exec() == QDialog::Accepted)
    {
        QString name = dialog.getName();
        if (!isNameValid(name))
        {
            QMessageBox::critical(this, "Error", "Configuration name isn't valid!");
        }
        else
        {
            QSettings *confList = QEMUSettings::getConfigurationList();
            QString list = confList->value("list").toString();
            if (!list.isEmpty())
                list += ",";
            list += name;
            confList->setValue("list", list);
            QTreeWidgetItem* configuration = new QTreeWidgetItem(this);
            configuration->setText(0, name);
            this->setCurrentItem(configuration);
        }
    }
}

bool ConfTreeWidget::isNameValid(const QString& name, bool isScenario)
{
    if (name.isEmpty())
        return false;

    if (isScenario)
    {
        QTreeWidgetItem *item = this->currentItem();
        int childCount = item->childCount();
        for (int j = 0; j < childCount; ++j)
            if (item->child(j)->text(0) == name)
                return false;
    }
    else
    {
        for (int i = 0; i < this->topLevelItemCount(); ++i)
        {
            QTreeWidgetItem *item = this->topLevelItem(i);
            if (item->text(0) == name)
                return false;
        }
    }

    return true;
}

/*void ConfTreeWidget::renameConf()
{
    QTreeWidgetItem* item = currentItem();
    this->oldName = item->text(0);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    editItem(item);
}

void ConfTreeWidget::checkRenamedItem(QWidget *editor, QAbstractItemDelegate::EndEditHint hint)
{
    Q_UNUSED(hint);

    QString newConfName = reinterpret_cast<QLineEdit*>(editor)->text();
    if (this->currentItem()->parent() == NULL)
    {
        if (!isNameValid(newConfName, 1))
        {
            QMessageBox::critical(this, "Error", "Configuration name isn't valid!");
            this->currentItem()->setText(0, oldName);
        }
    }
    else
    {
        if (!isNameValid(newConfName, 1, true))
        {
            QMessageBox::critical(this, "Error", "Scenario name isn't valid!");
            this->currentItem()->setText(0, oldName);
        }
    }

    this->currentItem()->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}*/

void ConfTreeWidget::removeItem(VMProperties *vm)
{
    if (this->currentItem() && this->currentItem()->parent() == NULL)
    {
        QDDeleteObject* dialog = new QDDeleteObject("Do you want to delete configuration?");
        if (dialog->exec() == QDialog::Accepted)
        {

            QTreeWidgetItem* configuration = this->takeTopLevelItem(this->indexOfTopLevelItem(this->currentItem()));
            VMProperties *settings = new VMProperties(configuration->text(0));
            if (settings)
            {
                settings->remove();
                delete settings;
            }

            QSettings* confList = QEMUSettings::getConfigurationList();
            if (confList)
            {
                QStringList data = confList->value("list").toString().split(",");
                data.removeAll(configuration->text(0));
                QString newData;
                foreach (QString chunck, data)
                    newData += "," + chunck;

                newData.remove(0, 1);
                confList->setValue("list", newData);
                delete confList;
            }

            delete configuration;
        }
        delete dialog;
    }
    else if (this->currentItem())
    {
        QDDeleteObject dialog("Do you want to delete scenario ?");
        if (dialog.exec() == QDialog::Accepted)
        {
            QTreeWidgetItem* item = this->currentItem();
            vm->removeScenario(item->text(0));
            QTreeWidgetItem* parent = item->parent();
            parent->removeChild(item);
            delete item;
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "There is no selected configuration!");
    }
}

bool ConfTreeWidget::addNewScenario(VMProperties *vm)
{
    QTreeWidgetItem *item = currentItem();
    if (item->parent() == NULL)
    {
        ReplayOptionsDialog dialog;
        if (dialog.exec() == QDialog::Accepted)
        {
            QString name = dialog.getRunName();
            bool isOk = isNameValid(name, true);
            if (!isOk)
            {
               QMessageBox::critical(this, "Error", "Run name isn't valid!");
               return false;
            }
            // add run to ini file first
            vm->addScenario(name);
            vm->setSnapshotsPeriod(name, dialog.getSnapshotsPeriod());
            // then update the tree to avoid wrong synchronization
            QTreeWidgetItem *scenario = new QTreeWidgetItem(item);
            scenario->setText(0, name);
            setCurrentItem(currentItem(), 0, QItemSelectionModel::Deselect);
            setCurrentItem(scenario, 0, QItemSelectionModel::Select);
            return true;
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Only configurations can have scenarios!");
        return false;
    }

    return false;
}

/*void ConfTreeWidget::renameScenario()
{
    QTreeWidgetItem* item = currentItem();
    this->oldName = item->text(0);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    editItem(item);
}*/

/*void ConfTreeWidget::saveScenarios(QSettings* configurationSettings, const QString& configurationName)
{
    QTreeWidgetItem* configuration = this->findItems(configurationName, Qt::MatchCaseSensitive).at(0);

    configurationSettings->setValue(QEMUSettings::getScenarioCount(), configuration->childCount());
    for (int i = 0; i < configuration->childCount(); ++i)
        configurationSettings->setValue
                (
                    QEMUSettings::getScenarioFileNameOption(i),
                    configuration->child(i)->text(0)
                 );
}*/

QString ConfTreeWidget::getCurrentScenario() const
{
    QTreeWidgetItem* item = this->currentItem();
    QTreeWidgetItem* parent = item->parent();

    return parent ? item->text(0) : "";
}

bool ConfTreeWidget::isConfigurationSelected() const
{
    QTreeWidgetItem* item = this->currentItem();
    return item && !item->parent();
}
