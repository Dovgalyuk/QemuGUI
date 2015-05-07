#include <QHostAddress>

#include "QEMU-GUI.h"
#include "ui_MainWindow.h"
#include "VMPropertiesDialog.h"
#include "GlobalSettingsDialog.h"

QEMUGUI::QEMUGUI(QWidget *parent) :
    QMainWindow(parent), currentVM(NULL), runningVM(NULL),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    this->isSaveRetrace = false;

    connect(ui->confTree,       SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),  this, SLOT(changeConfigurations(QTreeWidgetItem*,QTreeWidgetItem*)));
    connect(ui->actionExit,     SIGNAL(triggered()),                                            this, SLOT(close()));
    connect(ui->actionStart,    SIGNAL(triggered()),                                            this, SLOT(onExecuteAction()));
    connect(ui->actionRecord,   SIGNAL(triggered()),                                            this, SLOT(onRecordAction()));
    connect(ui->actionCreate,   SIGNAL(triggered()),                                            this, SLOT(on_addConfButton_clicked()));
    connect(ui->actionDelete,   SIGNAL(triggered()),                                            this, SLOT(on_deleteConfButton_clicked()));
    connect(ui->actionEdit,     SIGNAL(triggered()),                                            this, SLOT(on_editButton_clicked()));
    connect(ui->actionOptions,  SIGNAL(triggered()),                                            this, SLOT(showGlobalOptions()));

    // update totalOptionsLineEdit
    connect(ui->logFileName,       SIGNAL(editingFinished()),    this, SLOT(updateControlsState()));
    connect(ui->snapshotCheckBox,  SIGNAL(clicked()),            this, SLOT(updateControlsState()));
    connect(ui->logOptions,        SIGNAL(clicked(QModelIndex)), this, SLOT(updateControlsState()));
    connect(ui->additionalOptions, SIGNAL(editingFinished()),    this, SLOT(updateControlsState()));

    connect(&monitorSocket, SIGNAL(readyRead()), this, SLOT(terminalRead()));
    connect(ui->terminalInput->lineEdit(), SIGNAL(returnPressed()), this, SLOT(terminalWrite()));

    loadConfList();
}

QEMUGUI::~QEMUGUI()
{
    delete ui;
}

void QEMUGUI::loadConfList()
{
    QSettings *confList = QEMUSettings::getConfigurationList();
    if (confList->contains("list"))
    {
        QStringList data = confList->value("list").toString().split(",");
        if (data.size() == 1 && data.at(0).isEmpty())
            data.clear();
        foreach (QString chunck, data)
        {
            // configurations
            QTreeWidgetItem* item = new QTreeWidgetItem;
            item->setText(0, chunck);
            ui->confTree->addTopLevelItem(item);

            // scenarios
            VMProperties configurationSettings(chunck);
            QStringList scenarios = configurationSettings.getScenarios();
            foreach (QString name, scenarios)
            {
                QTreeWidgetItem *scenario = new QTreeWidgetItem(item);
                scenario->setText(0, name);
            }
        }
        if (data.size() > 0)
        {
            ui->confTree->setCurrentItem(ui->confTree->topLevelItem(0));
            changeConfiguration(ui->confTree->topLevelItem(0)->text(0));
        }
    }
    delete confList;
}

void QEMUGUI::on_startButton_clicked()
{
    if (!currentVM || runningVM)
        return;

    QStringList options = getConfigurationOptions();

    runningVM = new VMRunner(currentVM, options, this);
    connect(runningVM, SIGNAL(resultReady(QString, QString)), this, SLOT(onVMStopped(QString, QString)));

    // create directory for temporary files
    // and overlay files for HDD/CD/FDD
    currentVM->createWorkingDirectory(getRunName());
    if (isSaveRetrace)
        currentVM->createDiskImages(getRunName());

    QString currentDirectory = currentVM->getRunPath(getRunName());
    QDir::setCurrent(currentDirectory);

    runningVM->start();

    QHostAddress addr("127.0.0.1");
    monitorSocket.connectToHost(addr, 2014);

    ui->optionsTabs->setCurrentWidget(ui->terminalPage);

    QString output = QString("<font color=White>Starting ") + currentVM->getSimulatorPath();
    foreach (QString s, options)
        output += " " + s;
    output += "</font><br><br>";
    ui->terminalOutput->appendHtml(output);

    updateControlsState();
}

QString QEMUGUI::getTotalCmd(const QStringList& options) const
{
    QString tmp;
    foreach(QString chunck, options)
    {
        tmp += chunck + " ";
    }
    return tmp;
}

QString QEMUGUI::getRunName() const
{
    return ui->confTree->getCurrentScenario();
}

void QEMUGUI::loadSettings(const QString &name)
{
    delete currentVM;
    currentVM = NULL;
    currentVM = new VMProperties(name, this);
    // восстанавливаем значения

    // TODO?
    //ui->snapshotCheckBox->setChecked(currentVM->getSnapshot(getRunName()));
    ui->logFileName->setText(currentVM->getLogFile(getRunName()));
    ui->logOptions->setCheckedCells(currentVM->getLogOptions(getRunName()));
    ui->additionalOptions->setText(currentVM->getAdditionalRunOptions(getRunName()));
}

void QEMUGUI::on_addConfButton_clicked()
{
    ui->confTree->addNewConf();
}

void QEMUGUI::changeConfiguration(const QString &name)
{
    // Сделать изменение текущей конфигурации
    loadSettings(name);
    updateControlsState();
}

void QEMUGUI::on_deleteConfButton_clicked()
{
    ui->confTree->removeItem(currentVM);
}

/*void QEMUGUI::on_addNewVlanButton_clicked()
{
    ui->netTreeWidget->addNewVlan();
}*/

void QEMUGUI::on_editButton_clicked()
{
    if (currentVM)
    {
        VMPropertiesDialog dialog(this, currentVM);
        dialog.exec();
        updateControlsState();
    }
}

void QEMUGUI::changeConfigurations(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);

    delete currentVM;
    currentVM = NULL;

    if (current)
    {
        QString currentConfiguration = current->parent() == NULL ? current->text(0) : current->parent()->text(0);
        changeConfiguration(currentConfiguration);
    }
}

void QEMUGUI::showGlobalOptions()
{
    GlobalSettingsDialog dialog;
    dialog.exec();
    /*
    QDGlobalOptions* options = new QDGlobalOptions;

    if (options->exec() == QDialog::Accepted)
    {
        QEMUSettings::getGlobalSettings()->setDefaultQEMU(options->getQEMUPath());
        QEMUSettings::getGlobalSettings()->setConfigurationsPath(options->getConfigurationsPath());
    }

    delete options;*/
}

void QEMUGUI::updateControlsState()
{
    bool running = runningVM != NULL;
    // start button
    ui->actionStart->setEnabled(!running);
    // create button
    ui->actionCreate->setEnabled(!running);
    // edit button
    ui->actionEdit->setEnabled(!running
                               && currentVM->getScenarios().empty());
    // delete button
    ui->actionDelete->setEnabled(!running);
    // record button
    ui->actionRecord->setEnabled(
                !running && ui->confTree->isConfigurationSelected());
    // terminal input
    ui->terminalInput->setEnabled(running);
    // command line
    ui->totalOptionsLineEdit->setPlainText(
                (currentVM ? currentVM->getSimulatorPath() : QString()) + " " + getTotalCmd(getConfigurationOptions()));
    // snapshot box
    if (!running)
    {
        if (currentVM && !currentVM->getScenarios().empty())
        {
            if (ui->confTree->isConfigurationSelected())
                ui->snapshotCheckBox->setChecked(true);
            else
                ui->snapshotCheckBox->setChecked(false);
            ui->snapshotCheckBox->setEnabled(false);
        }
        else
        {
            ui->snapshotCheckBox->setEnabled(true);
        }
    }
    else
    {
        ui->snapshotCheckBox->setEnabled(false);
    }
    // log file
    ui->logFileName->setEnabled(!running);
    // log options
    ui->logOptions->setEnabled(!running/* && !ui->logFileName->text().isEmpty()*/);
    // other options
    ui->additionalOptions->setEnabled(!running);
    // configurations
    ui->confTree->setEnabled(!running);
}

QStringList QEMUGUI::getConfigurationOptions()
{
    QStringList options;
    updateVMOptions();

    bool isPlay = !ui->confTree->isConfigurationSelected() && !isSaveRetrace;
    if (currentVM)
        currentVM->fillCommandLine(options, getRunName(), isPlay);

    // snapshot
    if (ui->snapshotCheckBox->isChecked() && ui->confTree->isConfigurationSelected())
        options << "-snapshot";

    if (isSaveRetrace)
    {
        options << "-retrace-save";
        QString params = "fname=replay_log.bin,snapshot=off";
        QString period = currentVM->getSnapshotsPeriod(getRunName());
        if (!period.isEmpty())
            params += ",period=" + period;
        options << params;
    }
    else if (isPlay)
    {
        options << "-retrace-play" << "fname=replay_log.bin,snapshot=off";
    }

    // TODO: automatically select distinct port for every machine.
    options << "-monitor" << "tcp:127.0.0.1:2014,server";

    return options;
}


void QEMUGUI::updateVMOptions()
{
    if (!currentVM)
        return;

    currentVM->setLogFile(getRunName(), ui->logFileName->text());
    currentVM->setLogOptions(getRunName(), ui->logOptions->getCheckedCells());
    currentVM->setAdditionalRunOptions(getRunName(), ui->additionalOptions->text());

    //TODO: snapshot?
}

void QEMUGUI::onRecordAction()
{
    updateVMOptions();
    if (ui->confTree->addNewScenario(currentVM))
    {
        this->isSaveRetrace = true;
        on_startButton_clicked();
        this->isSaveRetrace = false;
    }
}

void QEMUGUI::onExecuteAction()
{
    on_startButton_clicked();
}

void QEMUGUI::onVMStopped(const QString &errorText, const QString &stdoutText)
{
    Q_UNUSED(errorText);
    Q_UNUSED(stdoutText);

    delete runningVM;
    runningVM = NULL;
    ui->terminalOutput->appendHtml("<font color=white>VM has stopped</font><br><br>");
    //ui->terminalOutput->appendPlainText(errorText);
    //ui->terminalOutput->appendPlainText(stdoutText);
    updateControlsState();
}

void QEMUGUI::terminalRead()
{
    QByteArray bytes = monitorSocket.readAll();
    QString text;
    char prev1 = 0;
    char prev2 = 0;
    bool processed = false;
    // process escape sequences
    foreach (char byte, bytes)
    {
        if (prev2 == 27 && prev1 == '[')
        {
            if (byte == 'D')
            {
                // truncate byte that already added to output
                if (text.size() < 3)
                {
                    QTextCursor cursor(ui->terminalOutput->document());
                    cursor.movePosition(QTextCursor::End);
                    cursor.deletePreviousChar();
                }
                text.truncate(text.size() - 3);
            }
            else
            {
                text.truncate(text.size() - 2);
            }
            processed = true;
        }
        else
        {
            text += byte;
            processed = false;
        }
        prev2 = prev1;
        prev1 = byte;
    }
    // trailing escape sequence
    if (prev2 == 27 && prev1 == '[' && !processed)
        text.truncate(text.size() - 2);
    // position cursor and insert text to avoid
    // inserting linefeed by appendPlainText function
    QTextCursor cursor(ui->terminalOutput->document());
    cursor.movePosition(QTextCursor::End);
    ui->terminalOutput->setTextCursor(cursor);
    ui->terminalOutput->insertPlainText(text);
    ui->terminalOutput->ensureCursorVisible();
}

void QEMUGUI::terminalWrite()
{
    //QString text = ui->terminalInput->text() + "\n";
    QString text = ui->terminalInput->lineEdit()->text() + "\n";
    QByteArray bytes = text.toAscii();
    monitorSocket.write(bytes);
    //ui->terminalInput->clear();
    ui->terminalInput->lineEdit()->clear();
    ui->terminalInput->setCurrentIndex(-1);
    //ui->terminalInput->insertItem(0, text);
}



