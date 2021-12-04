#ifndef ITERATOR_OBSERVER_POOL_H
#define ITERATOR_OBSERVER_POOL_H

#include <QSet>
#include <data/iterator.h>

template <class T>
class ObserverPoolIterator : public Iterator <T*>
{
public:
    ObserverPoolIterator(QList <T*> observerList) {
        this->list = observerList;
        iterator = this->list.begin();
    }

    bool hasNext() override {
        if(iterator == list.end())
            return false;
        return true;
    }

    T* next() {
        auto current = *iterator;
        ++iterator;
        return current;
    }

private:
    QList <T*> list;
    typename QList <T*>::iterator iterator;
};

#endif