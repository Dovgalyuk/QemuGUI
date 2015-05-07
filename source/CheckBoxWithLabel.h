#ifndef CHECKBOXWITHLABEL_H
#define CHECKBOXWITHLABEL_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QLayout>

class CheckBoxWithLabel : public QWidget
{
    Q_OBJECT
public:
    explicit CheckBoxWithLabel(QString textLabel, QWidget *parent = 0);
    bool isCheked();
    void setChecked(bool);
private:
    QCheckBox* checkBox;
    QLabel*    label;
signals:
    void checkBoxChecked(bool);
public slots:
    void sendCheckBoxChecked(int);
};

#endif // CHECKBOXWITHLABEL_H
