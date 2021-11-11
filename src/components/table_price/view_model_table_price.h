#ifndef VIEW_MODEL_TABLE_PRICE_H
#define VIEW_MODEL_TABLE_PRICE_H

#include <QtWidgets>
#include <memory>
#include <data/pair.h>


class PriceTableViewModel : public QObject
{
public:
    explicit PriceTableViewModel();
    void setPair(std::shared_ptr <Pair> pair);
private:
    std::shared_ptr <Pair> pair;
};

#endif