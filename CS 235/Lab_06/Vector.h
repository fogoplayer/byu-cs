#ifndef VECTOR_H_
#define VECTOR_H_

#include "Deque.h"

template <typename T>
class Vector
{
private:
    Deque<T> vectorDeque;

public:
    Vector(T seedData[] = {}, size_t seedDataSize = 0) : vectorDeque(Deque<T>(seedData, seedDataSize)){};
    ~Vector() {}
    /**
     * Remove the back node of the vector
     */
    void pop_back()
    {
        vectorDeque.pop_back();
    }

    /**
     * Push an element to the back of the vector
     * @param node the node being sent to the back of the vector
     */
    void push_back(const T &node)
    {
        vectorDeque.push_back(node);
    }

    /**
     * Determine if vector is empty
     * @return true if empty, false if not
     */
    bool empty() const
    {
        return vectorDeque.empty();
    }

    /**
     * Get the size of the vector
     */
    size_t size()
    {
        return vectorDeque.size();
    }

    /**
     * Find the element in the array
     * @param node the element to look for
     * @return a string of the index, or "false"
     */
    std::string find(T &node)
    {
        return vectorDeque.find(node);
    }

    /**
     * Gets the contents of the stack as a string
     * @return a string listing the contents of the stack
     */
    std::string toString()
    {
        return vectorDeque.toString();
    }

    /**
     * Overload the insertion
     * @return an ostream with the contents of the vector
     */
    friend std::ostream &operator<<(std::ostream &os, Vector &vectorObj)
    {
        os << vectorObj.toString();
        return os;
    }

    /**
     * Access the element at a certain index in the vector
     * @return a node
     */
    T &operator[](size_t index)
    {
        return vectorDeque.at(index);
    }

    /**
     * Access the element at a certain index in the vector
     * @return a node
     */
    T &at(size_t index)
    {
        return vectorDeque.at(index);
    }
};

#endif