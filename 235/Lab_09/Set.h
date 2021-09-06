#ifndef SET_H_
#define SET_H_

#include <iostream>
#include <sstream>

#include "SetInterface.h"
#include "BST.h"

template <typename T>
class Set : public SetInterface<T>
{
private:
    Bst<T> bst;

public:
    Set(){};
    ~Set(){};

    /** Inserts item into the set, if the container doesn't
		already contain an element with an equivalent value. */
    virtual bool insert(const T &item)
    {
        bst.addNode(item);
        return true;
    }

    /** Removes all items from the set. */
    virtual void clear(){};

    /** @return: the number of elements contained by the Set. */
    virtual size_t size() const
    {
        return 999;
    };

    /** @return: return 1 if contains element equivalent to item, else 0. */
    virtual size_t count(const T &item)
    {
        return (bst.find(item) == "found") ? 1 : 0;
    };

    /** @return: string representation of items in Set. */
    virtual std::string toString() const
    {
        return bst.toString();
    };

    /**
     * Overload the insertion operator
     * @return an ostream with Set
     */
    friend std::ostream &operator<<(std::ostream &os, Set &set)
    {
        os << set.toString();
        return os;
    }
};

#endif