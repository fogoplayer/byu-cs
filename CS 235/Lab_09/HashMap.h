#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <iostream>
#include <sstream>

#include "HashMapInterface.h"

template <typename K, typename V>
class HashMap : public HashMapInterface<K, V>
{
private:
public:
    HashMap();
    ~HashMap();

    /**
     * Read/write index access operator.
     * If the key is not found, an entry is made for it.
     * @return: Read and write access to the value mapped to the provided key. 
     */
    virtual V &operator[](const K &key) = 0;

    /**
     * @return: the number of elements that match the key in the Map.
     */
    virtual size_t count(const K &key) = 0;

    /**
     * Removes all items from the Map.
     */
    virtual void clear(void) = 0;

    /**
     * @return: number of Key-Value pairs stored in the Map.
     */
    virtual size_t size(void) const = 0;

    /**
     * @return: maximum number of Key-Value pairs that the Map can hold.
     */
    virtual size_t max_size(void) const = 0;

    /**
     * @return: string representation of Key-Value pairs in Map.
     */
    virtual std::string toString(void) const = 0;

    /**
     * Overload the insertion operator
     * @return an ostream with HashMap
     */
    friend std::ostream &operator<<(std::ostream &os, HashMap &hashMap)
    {
        os << hashMap.toString();
        return os;
    }
};

#endif