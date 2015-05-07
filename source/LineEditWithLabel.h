#ifndef LINEEDITWITHLABEL_H
#define LINEEDITWITHLABEL_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>

class LineEditWithLabel : public QWidget
{
    Q_OBJECT
public:
    explicit LineEditWithLabel(const QString& textLabel = QString(), QWidget *parent = 0);
    QString getText();
    void    setText(const QString& text);
private:
    QLineEdit*  lineEdit;
    QLabel*     label;
signals:

public slots:

};

#endif // LINEEDITWITHLABEL_H
