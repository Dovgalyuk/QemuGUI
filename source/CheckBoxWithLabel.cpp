#include "checkboxwithlabel.h"

CheckBoxWithLabel::CheckBoxWithLabel(QString textLabel, QWidget *parent) :
    QWidget(parent)
{
    checkBox    = new QCheckBox;
    label       = new QLabel(textLabel);

    QHBoxLayout* main = new QHBoxLayout;
    main->addWidget(label);
    main->addWidget(checkBox);

    connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(sendCheckBoxChecked(int)));

    this->setLayout(main);
}

bool CheckBoxWithLabel::isCheked()
{
    return checkBox->isChecked();
}

void CheckBoxWithLabel::sendCheckBoxChecked(int state)
{
    if (state == Qt::Unchecked)
        emit checkBoxChecked(false);
    else if (state == Qt::Checked)
        emit checkBoxChecked(true);
}

void CheckBoxWithLabel::setChecked(bool state)
{
    checkBox->setChecked(state);
}
