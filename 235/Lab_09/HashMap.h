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

    int getHashVal(const K &key);

    void checkAndRehash()
    {
        int tableLoad = size() * 100 / capacity;
        if (tableLoad <= LOAD_THRESHOLD)
        {
            return;
        }

        size_t old_capacity = capacity;
        capacity = capacity * 2;
        Pair<K, V> *new_pairArray = new Pair<K, V>[capacity];
        for (size_t index = 0; index < old_capacity; ++index)
        {
            if (pairArray[index].first != "")
            {
                size_t hashIndex = getHashVal(pairArray[index].first);
                int probe = -1;
                while (new_pairArray[hashIndex].first != "")
                {
                    probe = probe + 2;
                    hashIndex = (hashIndex + probe) % capacity;
                }
                // **Deep assignment
                new_pairArray[hashIndex] = pairArray[index];
            }
        }
        delete[] pairArray;
        pairArray = new_pairArray;
        return;
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
    virtual V &operator[](const K &key);

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
    virtual size_t size(void) const;

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
    virtual std::string toString(void) const;

    /**
     * Overload the insertion operator
     * @return an ostream with HashMap
     */
    friend std::ostream &
    operator<<(std::ostream &os, HashMap &hashMap)
    {
        os << hashMap.toString();
        return os;
    }
};

template <typename K, typename V>
int HashMap<K, V>::getHashVal(const K &key)
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

template <typename K, typename V>
V &HashMap<K, V>::operator[](const K &key)
{
    checkAndRehash();

    int tableIndex = getHashVal(key);
    size_t k = 1; // Quadratic probing

    while (1)
    {
        if (pairArray[tableIndex].first != K())
        {
            if (pairArray[tableIndex].first == key)
            {
                break;
            }
            tableIndex = (tableIndex + k) % capacity; // Quadratic probing
            k += 2;                                   // Quadratic probing
            // tableIndex = (tableIndex + 1) % capacity; // Linear probing
            continue;
        }
        pairArray[tableIndex].first = key;
        break;
    }

    return pairArray[tableIndex].second;
}

template <typename K, typename V>
size_t HashMap<K, V>::size(void) const
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

template <typename K, typename V>
std::string HashMap<K, V>::toString(void) const
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

#endif