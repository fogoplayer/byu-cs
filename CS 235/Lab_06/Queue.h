#ifndef QUEUE_H_
#define QUEUE_H_

#include "Deque.h"

template <typename T>
class Queue
{
private:
    Deque<T> queueDeque;

public:
    Queue() {}
    ~Queue() {}

    /**
     * Determine if queue is empty
     * @return true if empty, false if not
     */
    bool empty() const
    {
        return queueDeque.empty();
    }

    /**
     * Access top item of queue
     * @return the value of the top item of the queue, by reference
     */
    T &front()
    {
        return queueDeque.front();
    }

    /**
     * Remove the top item of the queue
     */
    void pop()
    {
        queueDeque.pop_front();
    }

    /**
     * Push an item onto the queue
     * @param item the item to push onto the queue
     */
    void push(const T &item)
    {
        queueDeque.push_back(item);
    }

    /**
     * Get the size of the queue
     */
    size_t size()
    {
        return queueDeque.size();
    }

    /**
     * Gets the contents of the queue as a string
     * @return a string listing the contents of the queue
     */
    std::string toString()
    {
        return queueDeque.toString();
    }

    /**
     * @return an ostream with the contents of the queue
     */
    friend std::ostream &operator<<(std::ostream &os, Queue &queueObj)
    {
        os << queueObj.toString();
        return os;
    }
};

#endif