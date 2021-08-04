#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <iostream>
#include <sstream>
#include <cmath>

#include "HashMapInterface.h"
#include "Pair.h"

template <typename K, typename V>
class HashMap : public HashMapInterface<K, V>
{
private:
    Pair<K, V> *pairArray;
    size_t capacity;

    int getHashVal(const K &key)
    {
        size_t tableIndex = 0;

        for (size_t i = 0; i < key.length(); i++)
        {
            // First character, multiply that by 3, add next character, multiply result by 3...
            tableIndex *= HASH_CONSTANT;
            tableIndex += key[i];
        }

        tableIndex %= capacity;

        return tableIndex;
    }

public:
    HashMap() : pairArray(new Pair<K, V>[DEFAULT_MAP_HASH_TABLE_SIZE]), capacity(DEFAULT_MAP_HASH_TABLE_SIZE){};
    ~HashMap()
    {
        delete[] pairArray;
        pairArray = nullptr;
        return;
    };

    /**
     * Read/write index access operator.
     * If the key is not found, an entry is made for it.
     * @return: Read and write access to the value mapped to the provided key. 
     */
    virtual V &operator[](const K &key)
    {
        int tableIndex = getHashVal(key);

        while (1)
        {
            if (pairArray[tableIndex].first != K())
            {
                if (pairArray[tableIndex].first == key)
                {
                    break;
                }
                tableIndex = (tableIndex + 1) % capacity;
                continue;
            }
            pairArray[tableIndex].first = key;
            break;
        }

        return pairArray[tableIndex].second;
    }

    /**
     * @return: the number of elements that match the key in the Map.
     */
    virtual size_t count(const K &key)
    {
        return 1;
    };

    /**
     * Removes all items from the Map.
     */
    virtual void clear(void){};

    /**
     * @return: number of Key-Value pairs stored in the Map.
     */
    virtual size_t size(void) const
    {
        size_t count = 0;
        for (size_t i = 0; i < capacity; i++)
        {
            if (pairArray[i].first != "")
            {
                ++count;
            }
        }

        return count;
    };

    /**
     * @return: maximum number of Key-Value pairs that the Map can hold.
     */
    virtual size_t max_size(void) const
    {
        return 1;
    };

    /**
     * @return: string representation of Key-Value pairs in Map.
     */
    virtual std::string toString(void) const
    {
        std::ostringstream os;
        os << size() << "/" << capacity << std::endl;
        for (size_t i = 0; i < capacity; i++)
        {
            std::cout << "  [" << i << ":" << pairArray[i].first << "->" << pairArray[i].second << "]" << std::endl;
            if (pairArray[i].first != K())
            {
                os << "  [" << i << ":" << pairArray[i].first << "->" << pairArray[i].second << "]" << std::endl;
            }
        }

        return os.str();
    }

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