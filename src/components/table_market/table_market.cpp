#include <QVariant>
#include "table_market.h"
#include "delegate_asset_title.h"
#include "delegate_asset_price.h"
#include "delegate_asset_price_change.h"

MarketTable::MarketTable(QString object_name) {
    setObjectName(object_name);
    this->setShowGrid(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->verticalHeader()->hide();

    tableModel = new QStandardItemModel(0, 3);
    this->setModel(tableModel);
    this->setItemDelegateForColumn(0, new AssetTitleDelegate(this));
    this->setItemDelegateForColumn(1, new AssetPriceDelegate(this));
    this->setItemDelegateForColumn(2, new AssetPriceChangeDelegate(this));

    QStringList headers = {"Pair", "Price", "24h Changes"};
    QHeaderView* header = this->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setDefaultAlignment(Qt::AlignLeft);
    
    tableModel->setHorizontalHeaderLabels(headers);
}

void MarketTable::clear() {
    pairContainer.clearAll();
    tableModel->removeRows(0, tableModel->rowCount());
}

void MarketTable::addPair(std::shared_ptr <Pair> pair) {
    pairContainer.add(pair);
    if(pairMatchesFilter(pair))
        displayPair(pair);
}

void MarketTable::displayPair(std::shared_ptr <Pair> pair) {
    QMap <QString, QString> data;
    data["symbol"] = pair->getSymbol();
    data["base"] = pair->getBaseSymbol();
    data["quote"] = pair->getQuoteSymbol();

    QVariant variantData;
    variantData.setValue(data);

    tableModel->insertRow(tableModel->rowCount());
    tableModel->setColumnCount(3);

    QModelIndex index = tableModel->index(
            tableModel->rowCount() - 1, 0, QModelIndex());

    tableModel->setData(index, variantData, Qt::DisplayRole);
}

void MarketTable::updatePairPrice(Price price) {
    QString pairSymbol = price.getPairSymbol();
    std::shared_ptr <Pair> pair = pairContainer.getBySymbol(pairSymbol);
    if(pair != nullptr) {
        QVariant variantData;
        variantData.setValue(price);

        // TODO: Optimize loop
        for(int i = 0; i < tableModel->rowCount(); ++i) {
            QModelIndex symbol_index = tableModel->index(i, 0, QModelIndex());
            QMap <QString, QString> delegate_data = symbol_index.data().value <QMap <QString, QString> >();

            if(delegate_data["symbol"] == pairSymbol) {
                QModelIndex price_index = tableModel->index(i, 1, QModelIndex());
                tableModel->setData(price_index, variantData, Qt::DisplayRole);
                break;
            }
        }
    }
}

void MarketTable::updatePairPriceChange(Price price) {
    QString pairSymbol = price.getPairSymbol();
    std::shared_ptr <Pair> pair = pairContainer.getBySymbol(pairSymbol);
    if(pair != nullptr) {
        QVariant variantData;
        variantData.setValue(price);

        for(int i = 0; i < tableModel->rowCount(); ++i) {
            QModelIndex symbol_index = tableModel->index(i, 0, QModelIndex());
            QMap <QString, QString> delegate_data = symbol_index.data().value <QMap <QString, QString> > ();

            if(delegate_data["symbol"] == pairSymbol) {
                QModelIndex change_index = tableModel->index(i, 2, QModelIndex());
                tableModel->setData(change_index, variantData, Qt::DisplayRole);
                break;
            }
        }
    }
}

bool MarketTable::pairMatchesFilter(std::shared_ptr <Pair> pair) {
    if(filter.isEmpty())
        return true;

    if(pair->getSymbol().toLower().startsWith(filter))
        return true;
    return false;
}

void MarketTable::setFilter(QString text) {
    this->filter = text.toLower();
    tableModel->removeRows(0, tableModel->rowCount());

    auto iterator = pairContainer.createIterator();
    while(iterator.hasNext()) {
        std::shared_ptr <Pair> pair = iterator.next();
        // if(pair == nullptr)
            // continue;

        if(pairMatchesFilter(pair))
            displayPair(pair);
    }
}