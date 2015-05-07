#include "lineeditwithlabel.h"

LineEditWithLabel::LineEditWithLabel(const QString &textLabel, QWidget *parent) :
    QWidget(parent)
{
    label       = new QLabel(textLabel);
    lineEdit    = new QLineEdit;

    QHBoxLayout* main = new QHBoxLayout;
    main->addWidget(label);
    main->addWidget(lineEdit);

    this->setLayout(main);
}

QString LineEditWithLabel::getText()
{
    return lineEdit->text();
}

void LineEditWithLabel::setText(const QString& text)
{
    lineEdit->setText(text);
}
