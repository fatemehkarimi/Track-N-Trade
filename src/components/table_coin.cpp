#include "table_coin.h"
#include "delegate_coin_title.h"

CoinTable::CoinTable(QString object_name) {
    setObjectName(object_name);
    this->setShowGrid(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->verticalHeader()->hide();

    this->setColumnCount(3);
    this->setHorizontalHeaderLabels(QStringList() << "Pair" << "Price" << "Change");
    QHeaderView* header = this->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

void CoinTable::clear() {
    setRowCount(0);
    clearContents();
}

void CoinTable::addCoin(Coin* coin) {
    QString title = coin->symbol().toUpper();
    insertRow(this->rowCount());
    this->setItemDelegateForRow(this->rowCount() - 1,
        new CoinTitleDelegate(this, title, "USD"));
}