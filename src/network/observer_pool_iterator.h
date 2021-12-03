#ifndef OBSERVER_POOL_ITERATOR_H
#define OBSERVER_POOL_ITERATOR_H

#include <QSet>
#include <data/iterator.h>

template <class T>
class ObserverPoolIterator : public Iterator <T> 
{
public:
    ObserverPoolIterator<T>(QSet <std::shared_ptr <T> > observerSet) {
        this->set = observerSet;
        // iterator = this->set.begin();
    }

    bool hasNext() override {
        // if(iterator == set.end())
            // return false;
        return true;
    }

    std::shared_ptr <T> next() {
        // auto current = iterator.value();
        // ++iterator;
        // return current;
        return nullptr;
    }

private:
    QSet <std::shared_ptr <T> > set;
    // QSet <std::shared_ptr <T> >::iterator iterator;
};

#endif