#include "container.h"

Container::Container() {

}

void Container::add(std::shared_ptr <APIItem> item) {
    QString id = item->getId();
    QString symbol = item->getSymbol();
    itemsById[id] = item;
    itemsBySymbol[id] = item;
}

std::shared_ptr <APIItem> Container::getById(QString id) {
    return itemsById[id];
}

std::shared_ptr <APIItem> Container::getBySymbol(QString symbol) {
    return itemsBySymbol[symbol];
}

void Container::removeById(QString id) {
    std::shared_ptr <APIItem> item = itemsById[id];
    if(item == nullptr)
        return;

    itemsById.remove(id);
    itemsBySymbol.remove(item->getSymbol());
}

void Container::removeBySymbol(QString symbol) {
    std::shared_ptr <APIItem> item = itemsBySymbol[symbol];
    if(item == nullptr)
        return;
    
    itemsBySymbol.remove(symbol);
    itemsById.remove(item->getId());
}