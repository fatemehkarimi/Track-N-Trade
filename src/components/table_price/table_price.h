#ifndef TABLE_PRICE_H
#define TABLE_PRICE_H

#include <QTableView>
#include <memory>
#include <data/pair.h>
#include <data/price.h>

class PriceTable : public QTableView {
    Q_OBJECT
public:
    explicit PriceTable(QString objectName);
    void setPair(std::shared_ptr <Pair> pair);
    void clear();
    void updatePrice(Price price);

private:
    std::shared_ptr <Pair> pair;
};

#endif