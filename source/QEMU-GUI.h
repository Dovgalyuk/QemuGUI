#ifndef QEMU_GUI_H
#define QEMU_GUI_H

#include <QMainWindow>
#include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QTreeWidgetItem>
#include <QTcpSocket>

#include "QEMUSettings.h"
#include "VMRunner.h"

namespace Ui {
class mainWindow;
}

class QEMUGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit QEMUGUI(QWidget *parent = 0);
    ~QEMUGUI();

private:
    QString getTotalCmd(const QStringList &options) const;
    QString getRunName() const;
    //void        saveSettings(const QString& name);
    void loadSettings(const QString& name);
    //void        clearSettings();
    void loadConfList();
    QStringList getConfigurationOptions();

    void on_startButton_clicked();

private:
    bool        isSaveRetrace;
    //QString     getActiveDirectory();
private:
    //! Properties of the currently selected VM.
    VMProperties *currentVM;
    //! Currently running VM.
    VMRunner *runningVM;
    //! Socket for connecting to monitor.
    QTcpSocket monitorSocket;

private slots:
    void on_addConfButton_clicked();
    void on_deleteConfButton_clicked();
    void on_editButton_clicked();
    void onRecordAction();
    void onExecuteAction();
    //void    on_addNewVlanButton_clicked();

    void    changeConfiguration(const QString& name);
    void    changeConfigurations(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void    showGlobalOptions();
    void    updateControlsState();
    void    updateVMOptions();

    void onVMStopped(const QString &errorText, const QString &stdoutText);
    void terminalRead();
    void terminalWrite();

private:
    Ui::mainWindow *ui;
};

#endif // QEMU_GUI_H
