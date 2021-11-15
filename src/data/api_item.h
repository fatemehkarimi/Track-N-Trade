#ifndef API_ITEM_H
#define API_ITEM_H

#include <QtWidgets>

class APIItem : public QObject{
public:
    virtual QString getId() = 0;
    virtual QString getSymbol() = 0;
};

#endif