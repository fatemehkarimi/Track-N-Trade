#ifndef OBSERVER_POOL_H
#define OBSERVER_POOL_H

#include "iterator_observer_pool.h"

template <class T>
class ObserverPool {
public:
    ObserverPool<T>(){}
    void registerObserver(QString url, T* observer) {
        for(auto o : pool[url])
            if(o == observer)
                return;
        pool[url].append(observer);
    }

    void removeObservers(QString url) {
        pool[url].clear();
    }

    void removeAll() {
        for(auto url : pool.keys())
            removeObservers(url);
        pool.clear();
    }

    ObserverPoolIterator<T> createIterator(QString url) {
        ObserverPoolIterator<T> iterator(pool[url]);
        return iterator;
    }

private:
    QMap <QString, QList <T*> > pool;
};

#endif