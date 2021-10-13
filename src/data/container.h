#ifndef CONTAINER_H
#define CONTAINER_H

#include <QMap>
#include <memory>
#include "api_item.h"

class Container {
public:
    explicit Container();

    void add(std::shared_ptr <APIItem> );
    std::shared_ptr <APIItem> getById(QString id);
    std::shared_ptr <APIItem> getBySymbol(QString symbol);
    void removeById(QString id);
    void removeBySymbol(QString symbol);

private:
    QMap <QString, std::shared_ptr <APIItem> > itemsById;
    QMap <QString, std::shared_ptr <APIItem> > itemsBySymbol;
};

#endif