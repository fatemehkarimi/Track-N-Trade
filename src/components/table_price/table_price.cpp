#include "table_price.h"

PriceTable::PriceTable(QString objectName) {
    setObjectName(objectName);
    viewModel = new PriceTableViewModel();
}

PriceTable::~PriceTable() {
    delete viewModel;
    viewModel = nullptr;
}

void PriceTable::setPair(std::shared_ptr <Pair> pair) {
    viewModel->setPair(pair);
}

void PriceTable::clear() {

}

void PriceTable::updatePrice(Price price) {
    
}