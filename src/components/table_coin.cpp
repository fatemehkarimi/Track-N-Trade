#include "table_coin.h"
#include "mydelegate.h"

CoinTable::CoinTable(QString object_name) {
    setObjectName(object_name);
    this->insertColumn(0);
}

void CoinTable::clear() {
    setRowCount(0);
    clearContents();
}

void CoinTable::addCoin(Coin* coin) {
    QString title = coin->symbol().toUpper();
    insertRow(this->rowCount());
    this->setItemDelegateForRow(this->rowCount() - 1, new MyDelegate(this, title, "USD"));
}