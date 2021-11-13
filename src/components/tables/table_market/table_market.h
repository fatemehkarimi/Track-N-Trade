#ifndef TABLE_MARKET_H
#define TABLE_MARKET_H

#include <memory>
#include <QTableView>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <data/pair.h>
#include <data/price.h>
#include <data/container.h>
#include <settings/settings_app.h>

class MarketTable : public QTableView
{
    Q_OBJECT
public:
    explicit MarketTable(QString objectName);
    void clear();
    void addPair(std::shared_ptr <Pair> pair);
    void updatePairPrice(Price price);
    void updatePairPriceChange(Price price);
    int getRowHeight();
    int getMinRowHeight();

public slots:
    void setFilter(QString text);

private slots:
    void handleRowSelection(const QModelIndex &current, const QModelIndex &previous);

signals:
    void assetListUpdated();
    void pairSelected(QString pair);

private:
    QString filter;
    QStandardItemModel* tableModel;
    Container <Pair> pairContainer;
    QMap <QString, Price> priceContainer;
    void displayPair(std::shared_ptr <Pair> pair);
    bool pairMatchesFilter(std::shared_ptr <Pair> pair);
};

#endif