#ifndef QTABLEVIEWCHECKBOX_H
#define QTABLEVIEWCHECKBOX_H

#include <QTableView>
#include <QStandardItemModel>
#include <QStringList>
#include <QHeaderView>


class QTableViewCheckBox : public QTableView
{
    Q_OBJECT
public:
    explicit QTableViewCheckBox(QWidget *parent = 0);
    QString getCheckedCells();
    void setCheckedCells(QString cells);
private:
    QStandardItemModel *model;
    int countRow, countCol;
    static const int constRowCount = 4;
    static const int constColCount = 3;
signals:

public slots:

};

#endif // QTABLEVIEWCHECKBOX_H
