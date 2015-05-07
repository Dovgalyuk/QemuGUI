#ifndef GLOBALSETTINGSDIALOG_H
#define GLOBALSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class GlobalSettingsDialog;
}

class GlobalSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GlobalSettingsDialog(QWidget *parent = 0);
    ~GlobalSettingsDialog();

    void addSimulator(QString name, QString path);
private slots:
    void on_removeButton_clicked();

    void on_addButton_clicked();

    void on_browseButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::GlobalSettingsDialog *ui;
};

#endif // GLOBALSETTINGSDIALOG_H
