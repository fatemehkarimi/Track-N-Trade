#ifndef ITERATOR_OBSERVER_POOL_H
#define ITERATOR_OBSERVER_POOL_H

#include <QSet>
#include <data/iterator.h>

template <class T>
class ObserverPoolIterator : public Iterator <std::shared_ptr <T> >
{
public:
    ObserverPoolIterator(QList <std::shared_ptr <T> > observerList) {
        this->list = observerList;
        iterator = this->list.begin();
    }

    bool hasNext() override {
        if(iterator == list.end())
            return false;
        return true;
    }

    std::shared_ptr <T> next() {
        auto current = *iterator;
        ++iterator;
        return current;
    }

private:
    QList <std::shared_ptr <T> > list;
    typename QList <std::shared_ptr <T> >::iterator iterator;
};

#endif