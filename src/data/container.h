#ifndef CONTAINER_H
#define CONTAINER_H

#include <QMap>
#include <memory>
#include "api_item.h"
#include "iterator_container.h"

template <class T>
class Container {
public:
    void add(std::shared_ptr <T> item) {
        QString id = item->getId();
        QString symbol = item->getSymbol();
        itemsById[id] = item;
        itemsBySymbol[symbol] = item;
    }

    std::shared_ptr <T> getById(QString id) {
        bool exists = itemsById.contains(id);
        if(exists) {
            std::shared_ptr <APIItem> item = itemsById[id];
            return std::static_pointer_cast <T>(item);
        }
        return nullptr;
    }

    std::shared_ptr <T> getBySymbol(QString symbol) {
        bool exists = itemsBySymbol.contains(symbol);
        if(exists){
            std::shared_ptr <APIItem> item = itemsBySymbol[symbol];
            return std::static_pointer_cast <T>(item);
        }
        return nullptr;
    }

    void removeById(QString id) {
        std::shared_ptr <APIItem> item = itemsById[id];
        if(item == nullptr)
            return;

        itemsById.remove(id);
        itemsBySymbol.remove(item->getSymbol());
    }

    void removeBySymbol(QString symbol) {
        std::shared_ptr <APIItem> item = itemsBySymbol[symbol];
        if(item == nullptr)
            return;
        
        itemsBySymbol.remove(symbol);
        itemsById.remove(item->getId());
    }

    void clearAll() {
        itemsById.clear();
        itemsBySymbol.clear();
    }

    bool empty() {
        return itemsById.empty();
    }

    ContainerIterator <T> createIterator() {
        ContainerIterator <T> iterator(itemsBySymbol);
        return iterator;
    }

    unsigned int size() {
        return itemsById.size();
    }

private:
    QMap <QString, std::shared_ptr <APIItem> > itemsById;
    QMap <QString, std::shared_ptr <APIItem> > itemsBySymbol;
};

#endif