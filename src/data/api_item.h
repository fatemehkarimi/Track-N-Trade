#ifndef API_ITEM_H
#define API_ITEM_H

class APIItem {
public:
    virtual QString getId() = 0;
    virtual QString getSymbol() = 0;
};

#endif