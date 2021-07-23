#ifndef DEQUE_H_
#define DEQUE_H_

#include <iostream>
#include <sstream>

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
                                                        tail(0) // FIXME Update so tail is outside of array
    {
        //First element
        container[0] = seedData[0];

        //Other elements;
        for (size_t i = 1; i < seedDataSize; ++i)
        {
            push_back(seedData[i]);
        }
    }
    ~Deque()
    {
        delete container;
    }

    /**
     * Add an element to the front of the deque
     * @param node the node being sent to the front of the deque
     */
    virtual void push_front(const T &node)
    {
        if (tail < (size_t)-1 && tail == head - 1 || // array has wrapped around and is now full
            head == 0 && tail == containerSize - 1)  // array is full from beginning to end
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
        if (tail < (size_t)-1 && tail == head - 1 || // array has wrapped around and is now full
            head == 0 && tail == containerSize - 1)  // array is full from beginning to end
        {
            reallocContainer();
        }

        tail = (tail + 1) % containerSize;
        container[tail] = node;

        return;
    }

    /**
     * Remove the front node of the deque
     */
    virtual void pop_front(void)
    {
        this->at(head) = 0;
        head = (head + 1) % containerSize;
        return;
    }

    /**
     * Remove the back node of the deque
     */
    virtual void pop_back(void)
    {
        this->at(tail) = 0;
        tail = (tail - 1) % containerSize;
        return;
    }

    /**
     * Retrieve the first node in the deque
     * @return a node
     */
    virtual T &front(void)
    {
        return this->at(head);
    }

    /**
     * Retrieve the last node in the deque
     * @return a node
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
     * Determine if the deque is empty
     * @return true if the deque is empty and false if it isn't
     */
    virtual bool empty(void) const
    {
        return head == tail && container[head] == 0;
    }

    /**
     * Access the element at a certain index in the deque
     * @return a node
     */
    virtual T &at(size_t index)
    {
        size_t realIndex = (head + index) % containerSize;
        return container[realIndex];
    }

    /**
     * Return a string with the contents of the deque
     */
    virtual std::string toString(void) const
    {
        std::ostringstream os;
        for (size_t i = 0; i < size(); i++)
        {
            size_t realIndex = (head + i) % containerSize;
            os << container[realIndex];
        }
        return os.str();
    }

    /**
     * @return an ostream with the contents of the deque
     */
    friend std::ostream &operator<<(std::ostream &os, Deque &deque)
    {
        os << deque.toString();
        return os;
    }
    //TODO braces operator?

private:
    /**
     * Reallocate the container
     * @param offset how far into the container array to start the array
     */
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
