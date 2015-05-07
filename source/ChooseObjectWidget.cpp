#include "chooseobjectwidget.h"

ChooseObjectWidget::ChooseObjectWidget(QWidget *parent) :
    QGroupBox(parent)
{
    objectPath          = new QLineEdit;
    getObjectPathButton = new QPushButton("Browse...");

    connect(getObjectPathButton,    SIGNAL(clicked()),          this, SLOT(getObjectPath()));
    connect(objectPath,             SIGNAL(editingFinished()),  this, SIGNAL(lineEditChanged()));

    QHBoxLayout* main = new QHBoxLayout;
    main->addWidget(objectPath); main->addWidget(getObjectPathButton);
    setLayout(main);
}

void ChooseObjectWidget::setMode(const QString& title, const QString& mode, const QString& caption, const QString& dir, const QString& filter)
{
    setTitle(title);
    this->mode      = mode;
    this->caption   = caption;
    this->dir       = dir;
    this->filter    = filter;
}

void ChooseObjectWidget::getObjectPath()
{
    QString path;
    if (mode == QString("file"))
        path = QFileDialog::getOpenFileName(this, caption, dir, filter);
    else if (mode == QString("dir"))
        path = QFileDialog::getExistingDirectory(this, caption, dir);

    if (!path.isEmpty())
        objectPath->setText(path);

    emit changedPath();
}

QString ChooseObjectWidget::getPath() const
{
    return objectPath->text();
}

void ChooseObjectWidget::setPath(const QString& path)
{
    objectPath->setText(path);
}
