#ifndef ITERATOR_H
#define ITERATOR_H

template <class T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual std::shared_ptr <T> next() = 0;
};

#endif