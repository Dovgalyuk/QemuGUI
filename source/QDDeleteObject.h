#ifndef QDDELETEOBJECT_H
#define QDDELETEOBJECT_H

#include <QDialog>
#include <QPushButton>
#include <QLayout>
#include <QLabel>

class QDDeleteObject : public QDialog
{
    Q_OBJECT
public:
    explicit QDDeleteObject(const QString& name, QWidget *parent = 0);

private:
    QPushButton* okButton;
    QPushButton* cancelButton;

signals:

public slots:

};

#endif // QDDELETEOBJECT_H
