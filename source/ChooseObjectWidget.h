#ifndef CHOOSEOBJECTWIDGET_H
#define CHOOSEOBJECTWIDGET_H

#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include "checkboxwithlabel.h"

class ChooseObjectWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit ChooseObjectWidget(QWidget *parent = 0);
    void    setMode(const QString& title = QString(), const QString& mode = QString(), const QString& caption = QString(), const QString& dir = QString(), const QString& filter = QString()); // caption, dir, filter
    QString getPath() const;
    void    setPath(const QString& path = QString());
private:
    QLineEdit*          objectPath;
    QPushButton*        getObjectPathButton;
    QString             mode;
    QString             caption;
    QString             dir;
    QString             filter;
signals:
    void changedPath();
    void lineEditChanged();
public slots:
    void getObjectPath();
};

#endif // CHOOSEOBJECTWIDGET_H
