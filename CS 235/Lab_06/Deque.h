#ifndef DEQUE_H_
#define DEQUE_H_

#include <iostream>

#include "DequeInterface.h"

template <typename T>
class Deque : public DequeInterface
{
public:
    /**
     * Create a deque
     * @param seedData an array of the data to prime the array with (defaults to empty)
     * @param seedDataSize the size of the seed data (defaults to 0)
     */
    Deque(T seedData[] = {}, size_t seedDataSize = 0) : container(new T[4]),
                                                        size(4),
                                                        head(0),
                                                        tail(0)
    {
        //First element
        container[0] = seedData[0];

        //Other elements;
        for (size_t i = 1; i < seedDataSize; ++i)
        {
            push_back(seedData[i]);
        }
    }
    ~Deque() {}

    /**
     * 
     */
    virtual void push_front(const T &value)
    {
        std::cout << "push_front" << std::endl;
    }

    /**
     * Push an element to the back of the deque
     * @param node the node being sent to the back of the deque
     */
    virtual void push_back(T node)
    {
        if (tail == head - 1 ||            // array has wrapped around and is now full
            head == 0 && tail == size - 1) // array is full from beginning to end
        {
            reallocContainer();
        }
        container[tail + 1] = node;
        ++tail;
    }

    /**
     * 
     */
    virtual void pop_front(void)
    {
        std::cout << "pop_front" << std::endl;
    }

    /**
     * 
     */
    virtual void pop_back(void)
    {
        std::cout << "pop_back" << std::endl;
    }

    /**
     * 
     */
    virtual T &front(void)
    {
        std::cout << "front" << std::endl;
    }

    /**
     * 
     */
    virtual T &back(void)
    {
        std::cout << "back" << std::endl;
    }

    /**
     * 
     */
    virtual size_t size(void) const
    {
        std::cout << "size" << std::endl;
    }

    /**
     * 
     */
    virtual bool empty(void) const
    {
        std::cout << "empty" << std::endl;
    }

    /**
     * 
     */
    virtual T &at(size_t index)
    {
        std::cout << "at" << std::endl;
    }

    /**
     * 
     */
    virtual std::string toString(void) const
    {
        std::cout << "toString" << std::endl;
    }

    //TODO Friend insertion member

private:
    void reallocContainer(int offset = 0)
    {
        T *newContainer = new T[size * 2];
        for (size_t i = 0; i < size; i++)
        {
            newContainer[i + offset] = container[i];
        }
        delete container;
        container = newContainer;
        size *= 2;
    }

    size_t size;
    size_t head;
    size_t tail;
    T *container;
};

#endif
