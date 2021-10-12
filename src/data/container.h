#ifndef CONTAINER_H
#define CONTAINER_H

#include <QMap>
#include "api_item.h"

class Container {
public:
    explicit Container();

    void add();
    void getById();
    void getBySymbol();
    void removeById();
    void removeBySymbol();

private:
    QMap <QString, std::shared_ptr <APIItem> > itemsById;
    QMap <QString, std::shared_ptr <APIItem> > itemsBySymbol;
};

#endif