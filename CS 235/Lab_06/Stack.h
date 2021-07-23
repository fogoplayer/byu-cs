#ifndef STACK_H_
#define STACK_H_

#include "Deque.h"

template <typename T>
class Stack
{
private:
    Deque<T> stackDeque;

public:
    Stack() {}
    ~Stack() {}

    /**
     * Determine if stack is empty
     * @return true if empty, false if not
     */
    bool empty() const
    {
        return stackDeque.empty();
    }

    /**
     * Access top item of stack
     * @return the value of the top item of the stack, by reference
     */
    T &top()
    {
        return stackDeque.front();
    }

    /**
     * Remove the top item of the stack
     */
    void pop()
    {
        stackDeque.pop_front();
    }

    /**
     * Push an item onto the stack
     * @param item the item to push onto the stack
     */
    void push(const T &item)
    {
        stackDeque.push_front(item);
    }

    /**
     * Get the size of the stack
     */
    size_t size()
    {
        return stackDeque.size();
    }

    /**
     * Gets the contents of the stack as a string
     * @return a string listing the contents of the stack
     */
    std::string toString()
    {
        return stackDeque.toString();
    }

    /**
     * @return an ostream with the contents of the stack
     */
    friend std::ostream &operator<<(std::ostream &os, Stack &stackObj)
    {
        os << stackObj.toString();
        return os;
    }
};

#endif