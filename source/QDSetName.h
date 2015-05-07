#ifndef QDSETNAME_H
#define QDSETNAME_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QFormLayout>
#include <QPushButton>

class QDSetName : public QDialog
{
    Q_OBJECT
public:
    explicit QDSetName(const QString& name, QWidget *parent = 0);
    QString getName();
private:
    QLineEdit*      lineEdit;
    QPushButton*    okButton;
signals:

public Q_SLOTS:
    virtual void accept();
};

#endif // QDSETNAME_H
