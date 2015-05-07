#ifndef CONFTREEWIDGET_H
#define CONFTREEWIDGET_H

#include <QTreeWidget>
#include <QMenu>
#include <QHeaderView>
#include <QScrollBar>
#include <QMessageBox>

#include "QEMUSettings.h"
#include "qdsetname.h"
#include "qddeleteobject.h"
#include "VMProperties.h"

class ConfTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ConfTreeWidget(QWidget *parent = 0);
    bool addNewScenario(VMProperties *vm);
    //void saveScenarios(QSettings* configurationSettings, const QString& configurationName);
    QString getCurrentScenario() const;
    bool isConfigurationSelected() const;
/*private:
    QMenu*          baseMenu;
    QAction*        bmAddNewConfiguration;

    QMenu*          confMenu;
    QAction*        cfmRenameConfigurationAction;
    QAction*        cfmRemoveConfigurationAction;
    //QAction*        cfmAddNewScenarioAction;

    QMenu*          scenarioMenu;
    QAction*        scmRemoveScenarioAction;
    QAction*        scmRenameScenarioAction;

    QString         oldName;*/

    bool isNameValid(const QString& name, bool isScenario = false);
signals:

public slots:
    void addNewConf();
    //void renameConf();
    void removeItem(VMProperties *vm);
    //void renameScenario();
private slots:
    //void contextMenuRequested(QPoint);

    //void checkRenamedItem(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
};

#endif // CONFTREEWIDGET_H
