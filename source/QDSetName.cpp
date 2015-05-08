#include "QDSetName.h"

QDSetName::QDSetName(const QString &name, QWidget *parent) :
    QDialog(parent)
{
    okButton =  new QPushButton("Create");
    lineEdit =  new QLineEdit;

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

    QFormLayout* main = new QFormLayout;
    main->addRow(name, lineEdit);
    main->addRow(okButton);

    setLayout(main);
}

QString QDSetName::getName()
{
    return lineEdit->text();
}

void QDSetName::accept()
{
    if (!lineEdit->text().isEmpty())
        QDialog::accept();
}
