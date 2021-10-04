#include <QVariant>
#include "table_coin.h"
#include "delegate_coin_title.h"
#include "delegate_coin_price.h"

CoinTable::CoinTable(QString object_name) {
    setObjectName(object_name);
    this->setShowGrid(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->verticalHeader()->hide();

    tableModel = new QStandardItemModel(0, 3);
    this->setModel(tableModel);
    this->setItemDelegateForColumn(0, new CoinTitleDelegate(this));
    this->setItemDelegateForColumn(1, new CoinPriceDelegate(this));

    QStringList headers = {"Pair", "Price", "24h Changes"};
    QHeaderView* header = this->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    tableModel->setHorizontalHeaderLabels(headers);
}

void CoinTable::clear() {
    coinList.clear();
    tableModel->removeRows(0, tableModel->rowCount());
}

void CoinTable::addCoin(std::shared_ptr <Coin> coin) {
    coinList[coin->symbol()] = coin;
    QString title = coin->symbol();
    QMap <QString, QString> data;
    data["symbol"] = title;
    data["unit"] = "USD";

    QVariant variantData;
    variantData.setValue(data);

    tableModel->insertRow(tableModel->rowCount());
    tableModel->setColumnCount(3);

    QModelIndex index = tableModel->index(
            tableModel->rowCount() - 1, 0, QModelIndex());
    tableModel->setData(index, variantData, Qt::DisplayRole);
}

void CoinTable::updateCoinPrice(QString symbol, Price price) {
    if(coinList[symbol] != nullptr) {
        QVariant variantData;
        variantData.setValue(price);

        // TODO: Optimize loop
        for(int i = 0; i < tableModel->rowCount(); ++i) {
            QModelIndex symbol_index = tableModel->index(i, 0, QModelIndex());
            QMap <QString, QString> delegate_data = symbol_index.data().value <QMap <QString, QString> >();

            if(delegate_data["symbol"] == symbol) {
                QModelIndex price_index = tableModel->index(i, 1, QModelIndex());
                tableModel->setData(price_index, variantData, Qt::DisplayRole);
                break;
            }
        }
    }
}