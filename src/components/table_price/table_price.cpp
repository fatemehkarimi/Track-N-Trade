#include <QVariant>
#include <components/table_market/delegate_asset_title.h>
#include "table_price.h"

PriceTable::PriceTable(QString objectName) {
    setObjectName(objectName);
    viewModel = new PriceTableViewModel();

    setTableViewProperties();
    setTableModel();
}

PriceTable::~PriceTable() {
    delete viewModel;
    viewModel = nullptr;
}

void PriceTable::setTableViewProperties() {
    this->setShowGrid(false);
    this->verticalHeader()->hide();
    this->horizontalHeader()->hide();
    this->setSelectionMode(QAbstractItemView::NoSelection);
}

void PriceTable::setTableModel() {
    tableModel = new QStandardItemModel(1, 5);
    this->setModel(tableModel);
    this->setItemDelegateForColumn(0, new AssetTitleDelegate(this));
}

void PriceTable::setPair(std::shared_ptr <Pair> pair) {
    viewModel->setPair(pair);
    displayPair(pair);
}

void PriceTable::displayPair(std::shared_ptr <Pair> pair) {
    QMap <QString, QString> data;
    data["symbol"] = pair->getSymbol();
    data["base"] = pair->getBaseSymbol();
    data["quote"] = pair->getQuoteSymbol();

    QVariant variantData;
    variantData.setValue(data);

    QModelIndex index = tableModel->index(0, 0, QModelIndex());
    tableModel->setData(index, variantData, Qt::DisplayRole);
}

void PriceTable::clear() {

}

void PriceTable::updatePrice(Price price) {
    
}