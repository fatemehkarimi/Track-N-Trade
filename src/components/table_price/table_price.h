#ifndef TABLE_PRICE_H
#define TABLE_PRICE_H

#include <QTableView>
#include <memory>
#include <data/pair.h>
#include <data/price.h>
#include "view_model_table_price.h"

class PriceTable : public QTableView {
    Q_OBJECT
public:
    explicit PriceTable(QString objectName);
    ~PriceTable();
    void setPair(std::shared_ptr <Pair> pair);
    void clear();
    void updatePrice(Price price);

private:
    std::shared_ptr <Pair> pair;
    PriceTableViewModel* viewModel;
};

#endif