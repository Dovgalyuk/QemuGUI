#include "QDDeleteObject.h"

QDDeleteObject::QDDeleteObject(const QString& name, QWidget *parent) :
    QDialog(parent)
{
    okButton        = new QPushButton("Ok");
    cancelButton    = new QPushButton("Cancel");

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton); buttonLayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    QVBoxLayout* main = new QVBoxLayout;
    main->addWidget(new QLabel(name)); //
    main->addLayout(buttonLayout);

    setLayout(main);
}
