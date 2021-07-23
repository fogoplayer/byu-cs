#ifndef DEQUE_H_
#define DEQUE_H_

#include <iostream>

#include "DequeInterface.h"

template <typename T>
class Deque : public DequeInterface<T>
{
public:
    /**
     * Create a deque
     * @param seedData an array of the data to prime the array with (defaults to empty)
     * @param seedDataSize the size of the seed data (defaults to 0)
     */
    Deque(T seedData[] = {}, size_t seedDataSize = 0) : container(new T[4]),
                                                        containerSize(4),
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
    virtual void push_front(const T &node)
    {
        if (tail == head - 1 ||                     // array has wrapped around and is now full
            head == 0 && tail == containerSize - 1) // array is full from beginning to end
        {
            reallocContainer(1);
        }

        head = head == 0 ? containerSize - 1 : (head - 1) % containerSize;
        container[head] = node;

        return;
    }

    /**
     * Push an element to the back of the deque
     * @param node the node being sent to the back of the deque
     */
    virtual void push_back(const T &node)
    {
        if (tail == head - 1 ||                     // array has wrapped around and is now full
            head == 0 && tail == containerSize - 1) // array is full from beginning to end
        {
            reallocContainer();
        }

        tail = (tail + 1) % containerSize;
        container[tail] = node;

        return;
    }

    /**
     * 
     */
    virtual void pop_front(void)
    {
        this->at(head) = 0;
        head = (head + 1) % containerSize;
        return;
    }

    /**
     * 
     */
    virtual void pop_back(void)
    {
        this->at(tail) = 0;
        tail = (tail - 1) % containerSize;
        return;
    }

    /**
     * 
     */
    virtual T &front(void)
    {
        return this->at(head);
    }

    /**
     * 
     */
    virtual T &back(void)
    {
        return this->at(tail);
    }

    /**
     * 
     */
    virtual size_t size(void) const
    {
        return tail > head ? tail - head : (tail + 1) + (containerSize - head); // # items in front of tail + # items after head
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
        size_t realIndex = (head + index) % containerSize;
        return container[realIndex];
    }

    /**
     * 
     */
    virtual std::string toString(void) const
    {
        std::cout << "toString" << std::endl;
    }

    //TODO Friend insertion member
    //TODO braces operator?

private:
    void reallocContainer(int offset = 0)
    {
        T *newContainer = new T[containerSize * 2];
        for (size_t i = 0; i < containerSize; i++)
        {
            newContainer[i + offset] = this->at(i);
        }
        delete container;
        container = newContainer;
        head = offset;
        tail = containerSize - 1 + offset;
        containerSize *= 2;
    }

    size_t containerSize;
    size_t head;
    size_t tail;
    T *container;
};

#endif
