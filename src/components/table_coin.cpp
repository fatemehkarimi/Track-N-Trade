#include <QVariant>
#include "table_coin.h"
#include "delegate_coin_title.h"

CoinTable::CoinTable(QString object_name) {
    setObjectName(object_name);
    this->setShowGrid(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->verticalHeader()->hide();

    tableModel = new QStandardItemModel(0, 3);
    this->setModel(tableModel);
    this->setItemDelegateForColumn(0, new CoinTitleDelegate(this));
}

void CoinTable::clear() {
    tableModel->clear();
    tableModel->setRowCount(0);
    tableModel->setColumnCount(3);////
}

void CoinTable::addCoin(std::shared_ptr <Coin> coin) {
    QString title = coin->symbol().toUpper();
    QMap <QString, QString> data;
    data["symbol"] = title;
    data["unit"] = "USD";

    QVariant variantData;
    variantData.setValue(data);

    tableModel->insertRow(tableModel->rowCount());
    tableModel->setColumnCount(3);////

    QModelIndex index = tableModel->index(tableModel->rowCount() - 1, 0, QModelIndex());
    tableModel->setData(index, variantData, Qt::DisplayRole);
}