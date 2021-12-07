#ifndef TABLE_PRICE_H
#define TABLE_PRICE_H

#include <QTableView>
#include <memory>
#include <data/pair.h>
#include <data/price.h>
#include <data/price_change.h>
#include <data/observer_single_pair_price.h>

class PriceTable : public QTableView, public SinglePairPriceObserver {
    Q_OBJECT
public:
    explicit PriceTable(QString objectName);
    ~PriceTable();
    void clear();
    void resizeEvent(QResizeEvent* event) override;
    void notifyPriceUpdate(std::shared_ptr <Pair> pair, Price price) override;
    void notifyPriceChangeUpdate(std::shared_ptr <Pair> pair, PriceChange priceChange) override;
    void notifyLowestPriceUpdate(std::shared_ptr <Pair> pair, Price price) override;
    void notifyHighestPriceUpdate(std::shared_ptr <Pair> pair, Price price) override;

private:
    void setTableModel();
    void styleTableView();
    void styleVerticalHeader();
    void styleHorizontalHeader();
    void adjustColumnsWidth();
    void styleHeaders();
    void displayPair(std::shared_ptr <Pair> pair);
    void displayPrice(Price price);
    void displayPriceChange(PriceChange priceChange);
    void displayLowestPrice(Price price);
    void displayHighestPrice(Price price);
    int getRowHeight();
    int getMinRowHeight();
    
    QStandardItemModel* tableModel;
};

#endif