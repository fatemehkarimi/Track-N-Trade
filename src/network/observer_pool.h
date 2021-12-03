#ifndef OBSERVER_POOL_H
#define OBSERVER_POOL_H

#include "observer_pool_iterator.h"

template <class T>
class ObserverPool {
public:
    ObserverPool<T>(){}
    void registerObserver(QString url, std::shared_ptr<T> observer) {
        if(pool[url].contains(observer))
            return;

        pool[url].insert(observer);
    }

    void removeObserver(QString url, std::shared_ptr<T> observer) {
        pool[url].remove(observer);
    }

    ObserverPoolIterator<T> createIterator(QString url) {
        ObserverPoolIterator<T> iterator(pool[url]);
        return iterator;
    }

private:
    QMap <QString, QSet <std::shared_ptr <T> > > pool;
};

#endif