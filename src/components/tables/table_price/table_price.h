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
    void resizeEvent(QResizeEvent* event) override;

private:
    void setTableModel();
    void styleTableView();
    void styleVerticalHeader();
    void styleHorizontalHeader();
    void adjustColumnsWidth();
    void styleHeaders();
    void displayPair(std::shared_ptr <Pair> pair);
    int getRowHeight();
    int getMinRowHeight();
    
    std::shared_ptr <Pair> pair;
    PriceTableViewModel* viewModel;
    QStandardItemModel* tableModel;
};

#endif