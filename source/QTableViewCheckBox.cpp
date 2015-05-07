#include "qtableviewcheckbox.h"

QTableViewCheckBox::QTableViewCheckBox(QWidget *parent) :
    QTableView(parent)
{

    // TODO: сделать добавление автоматизированным, допустим, считывать из файла, автоматически рассчитывать количество столбцов/ячеек

    QStringList list;
    list << "out_asm" << "in_asm" << "op" << "op_opt"
         << "int" << "exec" << "cpu" << "pcall"
         << "cpu_reset" << "ioport" << "unimp"
         << "guest_errors" << "retrace" << "retrace2";

    model = new QStandardItemModel(constRowCount, constColCount);

    countRow = 0;
    countCol = 0;

    foreach(QString item, list)
    {
        QStandardItem* modelItem = new QStandardItem(item);
        modelItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        modelItem->setData(Qt::Unchecked, Qt::CheckStateRole);
        model->setItem(countRow++, countCol, modelItem);
        if (countRow > 4)
        {
            countCol++;
            countRow = 0;
        }
    }

    this->setModel(model);
    this->verticalHeader()->hide();
    this->horizontalHeader()->hide();
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

QString QTableViewCheckBox::getCheckedCells()
{
    QString checkedCells;
    for (int i = 0; i <= constRowCount; ++i)
        for (int j = 0; j < constColCount; ++j)
        {
            QModelIndex index = model->index(i, j);
            if (index.data(Qt::CheckStateRole) == Qt::Checked)
            {
                if (!checkedCells.isEmpty())
                    checkedCells.push_back(',');
                checkedCells.push_back(index.data().toString());
            }
        }

    return checkedCells;
}

void QTableViewCheckBox::setCheckedCells(QString cells)
{
    QStringList cellsList = cells.split(',');
    for (int i = 0 ; i <= constRowCount ; ++i)
        for (int j = 0 ; j < constColCount ; ++j)
        {
            QModelIndex index = model->index(i, j);
            if (index.data().isNull())
                continue;

            if (cellsList.contains(index.data().toString()))
            {
                model->setData(index, Qt::Checked, Qt::CheckStateRole);
            }
            else
            {
                if (!index.data().toString().isEmpty())
                    model->setData(index, Qt::Unchecked, Qt::CheckStateRole);
            }
        }
}
