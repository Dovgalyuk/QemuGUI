#ifndef NETTREEWIDGET_H
#define NETTREEWIDGET_H

#include <QTreeWidget>
#include <QHeaderView>
#include <QMenu>
#include <QScrollBar>
#include "QDNetConfiguration.h"
#include "VMProperties.h"

class NetTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit NetTreeWidget(QWidget *parent = 0);
    void saveSettings(VMProperties *vm);
    void loadSettings(VMProperties *vm);
    //void clearSettings();
    //void getSettings(QStringList& settings);
private:
    /*QMenu* treeMenu;
    QAction* tmAddRootAction;

    QMenu* rootMenu;
    QAction* rmRemRootAction;
    QAction* rmAddNewConfigurationAction;
    QAction* rmRemConfiguration;

    QMenu* netOptionMenu;
    QAction* nomEditNetOptionAction;*/

    int vlanCount;
    void addRoot(const QString& text);
signals:
    void changeConfiguration();
private slots:
    //void contextMenuRequested(QPoint point);
    //void addNewConf();
    //void removeConf();
public slots:
    void addVlan();
    void addNic();
    void editNic();
    void removeItem();
};

#endif // NETTREEWIDGET_H
