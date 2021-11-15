#include <QVariant>
#include <settings/settings_app.h>
#include <components/tables/table_delegates/delegate_pair.h>
#include <components/tables/table_delegates/delegate_price.h>
#include <components/tables/table_delegates/delegate_price_change.h>
#include "table_market.h"

MarketTable::MarketTable(QString objectName) {
    setObjectName(objectName);
    this->setShowGrid(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->verticalHeader()->hide();
    this->setSelectionMode(QAbstractItemView::SingleSelection);

    Settings::Font fontSettings = Settings::App::getInstance()->getFontSettings();
    tableModel = new QStandardItemModel(0, 3);
    this->setModel(tableModel);
    this->setItemDelegateForColumn(
        0, new PairDelegate(this, fontSettings.getMarketTablePairFont()));
    this->setItemDelegateForColumn(
        1, new PriceDelegate(this, fontSettings.getMarketTablePriceFont()));
    this->setItemDelegateForColumn(
        2, new PriceChangeDelegate(this, fontSettings.getMarketTablePriceChangeFont()));

    QItemSelectionModel* selectedRow = this->selectionModel();
    QObject::connect(selectedRow, &QItemSelectionModel::currentRowChanged,
        this, &MarketTable::handleRowSelection);

    QStringList headers = {"Pair", "Price", "24h Changes"};
    QHeaderView* horizontalHeader = this->horizontalHeader();
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader->setDefaultAlignment(Qt::AlignLeft);
    tableModel->setHorizontalHeaderLabels(headers);

    this->verticalHeader()->setDefaultSectionSize(
        std::max(getRowHeight(), getMinRowHeight()));
}

int MarketTable::getRowHeight() {
    Settings::Font& fontSettings = Settings::App::getInstance()->getFontSettings();
    QFont titleFont = fontSettings.getMarketTablePairFont();
    QFont priceFont = fontSettings.getMarketTablePriceFont();
    QFont priceChangeFont = fontSettings.getMarketTablePriceChangeFont();

    QFontMetrics titleFontMetrics(titleFont);
    QFontMetrics priceFontMetrics(priceFont);
    QFontMetrics priceChangeFontMetrics(priceChangeFont);

    return std::max(std::max(titleFontMetrics.height(),
                    priceFontMetrics.height()),
                    priceChangeFontMetrics.height()) + 10;
}

int MarketTable::getMinRowHeight() {
    return 25;
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
    QVariant variantData;
    variantData.setValue(pair);

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
        priceContainer[pairSymbol] = price;
        QVariant variantData;
        variantData.setValue(price);

        // TODO: Optimize loop
        for(int i = 0; i < tableModel->rowCount(); ++i) {
            QModelIndex symbol_index = tableModel->index(i, 0, QModelIndex());
            std::shared_ptr <Pair> pair = 
                symbol_index.data().value <std::shared_ptr <Pair> >();

            if(pair == nullptr)
                return;

            if(pair->getSymbol() == pairSymbol) {
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
        priceContainer[pairSymbol] = price;
        QVariant variantData;
        variantData.setValue(price);

        for(int i = 0; i < tableModel->rowCount(); ++i) {
            QModelIndex symbol_index = tableModel->index(i, 0, QModelIndex());
            std::shared_ptr <Pair> pair = 
                symbol_index.data().value <std::shared_ptr <Pair> > ();
            
            if(pair == nullptr)
                return;

            if(pair->getSymbol() == pairSymbol) {
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

        if(pairMatchesFilter(pair)) {
            displayPair(pair);
            if(priceContainer.contains(pair->getSymbol())) {
                updatePairPrice(priceContainer[pair->getSymbol()]);
                updatePairPriceChange(priceContainer[pair->getSymbol()]);
            }
        }
    }
}

void MarketTable::handleRowSelection(
    const QModelIndex &current, const QModelIndex &previous) {
    int row = current.row();
    QModelIndex currentPair = tableModel->index(row, 0, QModelIndex());
    std::shared_ptr <Pair> pair = 
        currentPair.data().value <std::shared_ptr <Pair> > ();
    
    if(pair == nullptr)
        return;
    QString pairSymbol = pair->getSymbol();
    // when table is cleared it triggers the currentRowChanged signal
    if(pairSymbol.isEmpty())
        return;
    emit pairSelected(pairSymbol);
}