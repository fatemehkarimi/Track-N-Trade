#ifndef ITERATOR_CONTAINER_H
#define ITERATOR_CONTAINER_H

#include <QtWidgets>
#include "iterator.h"
#include "api_item.h"

template <class T>
class ContainerIterator : public Iterator <std::shared_ptr <T> >
{
public:
    ContainerIterator<T>(QMap <QString, std::shared_ptr <APIItem> > items) {
        itemList = items;
        iterator = itemList.begin();
    }

    std::shared_ptr <T> next() override {
        auto current = std::static_pointer_cast <T>(iterator.value());
        ++iterator;
        return current;
    }

    bool hasNext() override {
        if(iterator == itemList.end())
            return false;
        return true;
    }

private:
    QMap <QString, std::shared_ptr <APIItem> > itemList;
    QMap <QString, std::shared_ptr <APIItem> >::iterator iterator;
};

#endif