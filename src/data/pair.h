#ifndef PAIR_H
#define PAIR_H

#include <QtWidgets>
#include "asset.h"
#include "api_item.h"

Q_DECLARE_SMART_POINTER_METATYPE(std::shared_ptr)

class Pair : public APIItem {
public:
    Pair(QString id, QString symbol,
        std::shared_ptr <Asset> base, std::shared_ptr <Asset> quote);
    QString getId() override;
    QString getSymbol() override;
    QString getBaseSymbol();
    QString getQuoteSymbol();
    std::shared_ptr <Asset> getBase();
    std::shared_ptr <Asset> getQuote();

private:
    QString id;
    QString symbol;
    std::shared_ptr <Asset> base;
    std::shared_ptr <Asset> quote;
};

#endif