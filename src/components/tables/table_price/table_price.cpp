#include <QVariant>
#include <data/pair.h>
#include <settings/settings_app.h>
#include <components/tables/table_delegates/delegate_pair.h>
#include <components/tables/table_delegates/delegate_price.h>
#include <components/tables/table_delegates/delegate_price_change.h>
#include "table_price.h"

PriceTable::PriceTable(QString objectName) {
    setObjectName(objectName);
    setTableModel();
    styleTableView();
    styleHeaders();
    hideLabels();
}

PriceTable::~PriceTable() {
}

void PriceTable::styleTableView() {
    this->setShowGrid(false);
    this->verticalHeader()->hide();
    this->setSelectionMode(QAbstractItemView::NoSelection);
}

void PriceTable::styleHeaders() {
    this->styleHorizontalHeader();
    this->styleVerticalHeader();
}

void PriceTable::styleHorizontalHeader() {
    this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    adjustColumnsWidth();
    this->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
}

void PriceTable::styleVerticalHeader() {
    this->verticalHeader()->setDefaultSectionSize(
        std::max(getRowHeight(), getMinRowHeight()));
}

void PriceTable::adjustColumnsWidth() {
    this->setColumnWidth(1, this->width() / 5);
    this->setColumnWidth(2, this->width() / 6);
    this->setColumnWidth(3, this->width() / 6);
    this->setColumnWidth(4, this->width() / 6);
}

void PriceTable::setTableModel() {
    Settings::Font fontSettings = Settings::App::getInstance()->getFontSettings();
    tableModel = new QStandardItemModel(1, 5);
    this->setModel(tableModel);
    this->setItemDelegateForColumn(
        0, new PairDelegate(this, fontSettings.getPriceTableAssetFont()));
    this->setItemDelegateForColumn(
        1, new PriceDelegate(this, fontSettings.getPriceTablePriceFont()));
    this->setItemDelegateForColumn(
        2, new PriceChangeDelegate(this, fontSettings.getPriceTablePriceChangeFont()));
    this->setItemDelegateForColumn(
        3, new PriceDelegate(this, fontSettings.getPriceTableLowestPriceFont()));
    this->setItemDelegateForColumn(
        4, new PriceDelegate(this, fontSettings.getPriceTableHighestPriceFont()));

    QStringList headers = {
        "Pair", "Price", "24h Changes",
        "highest 24h price", "lowest 24h price"};
    tableModel->setHorizontalHeaderLabels(headers);
}

int PriceTable::getRowHeight() {
    Settings::Font& fontSettings = Settings::App::getInstance()->getFontSettings();
    QFont titleFont = fontSettings.getPriceTableAssetFont();
    QFont priceFont = fontSettings.getPriceTablePriceFont();
    QFont priceChangeFont = fontSettings.getPriceTablePriceChangeFont();

    QFontMetrics titleFontMetrics(titleFont);
    QFontMetrics priceFontMetrics(priceFont);
    QFontMetrics priceChangeFontMetrics(priceChangeFont);

    return std::max(std::max(titleFontMetrics.height(),
                    priceFontMetrics.height()),
                    priceChangeFontMetrics.height()) + 10;
}

int PriceTable::getMinRowHeight() {
    return 25;
}

void PriceTable::displayPair(std::shared_ptr <Pair> pair) {
    QVariant variantData;
    variantData.setValue(pair);

    QModelIndex index = tableModel->index(0, 0, QModelIndex());
    tableModel->setData(index, variantData, Qt::DisplayRole);
}

void PriceTable::displayPrice(Price price) {
    QVariant variantData;
    variantData.setValue(price);

    QModelIndex index = tableModel->index(0, 1, QModelIndex());
    tableModel->setData(index, variantData, Qt::DisplayRole);
}

void PriceTable::displayPriceChange(PriceChange priceChange) {
    QVariant variantData;
    variantData.setValue(priceChange);

    QModelIndex index = tableModel->index(0, 2, QModelIndex());
    tableModel->setData(index, variantData, Qt::DisplayRole);
}

void PriceTable::displayLowestPrice(Price price) {
    QVariant variantData;
    variantData.setValue(price);
    
    QModelIndex index = tableModel->index(0, 3, QModelIndex());
    tableModel->setData(index, variantData, Qt::DisplayRole);
}

void PriceTable::displayHighestPrice(Price price) {
    QVariant variantData;
    variantData.setValue(price);

    QModelIndex index = tableModel->index(0, 4, QModelIndex());
    tableModel->setData(index, variantData, Qt::DisplayRole);
}

void PriceTable::hideLabels() {
    this->horizontalHeader()->hide();
}

void PriceTable::showLabels() {
    this->horizontalHeader()->show();
}

void PriceTable::clear() {
    for(int i = 0; i < tableModel->columnCount(); ++i)
        tableModel->clearItemData(tableModel->index(0, i, QModelIndex()));
    hideLabels();
}

void PriceTable::resizeEvent(QResizeEvent* event) {
    this->adjustColumnsWidth();
}

void PriceTable::notifyPriceUpdate(std::shared_ptr <Pair> pair, Price price) {
    showLabels();
    displayPair(pair);
    displayPrice(price);
}

void PriceTable::notifyPriceChangeUpdate(std::shared_ptr <Pair> pair,
    PriceChange priceChange) {
    displayPriceChange(priceChange);
}

void PriceTable::notifyLowestPriceUpdate(
    std::shared_ptr <Pair> pair, Price price) {
    displayLowestPrice(price);
}

void PriceTable::notifyHighestPriceUpdate(
    std::shared_ptr <Pair> pair, Price price) {
    displayHighestPrice(price);
}