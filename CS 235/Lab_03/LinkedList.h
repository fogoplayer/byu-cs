#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include <sstream>
#include <string>

#include "LinkedListInterface.h"

template <typename T>
class LinkedList : public LinkedListInterface<T>
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &data, Node *next = NULL) : data(data), next(next) {}
    };
    Node *head;

public:
    LinkedList() : LinkedListInterface<T>(), head(NULL) {}
    ~LinkedList() {}

    /**
     * Add an element to the front of the list
     * @param value a value to be added to the front of the list
     * @return void
     */
    void push_front(const T &value)
    {
        std::cout << "Push front" << std::endl;
        head = new Node(value, head);
        return;
    }

    /**
     * Remove the first element of the list. Throws a string error message if list is empty
     * @return void
     */
    void pop_front(void)
    {
        std::cout << "Pop front" << std::endl;
        if (head != NULL)
        {
            std::string errMsg = "Empty!";
            throw errMsg;
        }
        Node *newHead = head->next;
        delete head;
        head = newHead;
    }

    /**
     * Get the first element in the list. Throws a string error message if list is empty
     * @return the first element in the list
     */
    T &front(void)
    {
        std::cout << "Front" << std::endl;
        if (head == NULL)
        {
            std::string errMsg = "Empty!";
            throw errMsg;
        }
        return head->data;
    }

    /**
     * Query if the list is empty
     * @return true if empty, otherwise false
     */
    bool empty(void) const
    {
        std::cout << "Empty" << std::endl;
        return (head == NULL);
    }

    /**
     * Find value and remove it. Throws a string error message if list is empty
     * @param value the value to be removed
     * @return void
     */
    void remove(const T &value)
    {
        std::cout << "Remove" << std::endl;
    }

    /**
     * Delete the list
     * @return void
     */
    void clear(void)
    {
        std::cout << "Clear" << std::endl;
    }

    /**
     * Reverse the order of the list. Throws a string error message if list is empty
     * @return void
     */
    void reverse(void)
    {
        std::cout << "Reverse" << std::endl;
    }

    /**
     * Get the size of the list
     * @return the size of the list as a size_t
     */
    size_t size(void) const
    {
        std::cout << "Size" << std::endl;
        return 1;
    }

    /**
     * Get the contents of the list as a string
     * @return the contents of the list as a string
     */
    std::string toString(void) const
    {
        std::cout << "To String" << std::endl;
        std::ostringstream listAsString("");

        Node *currNode = head;
        while (currNode != NULL)
        {
            listAsString << " " << currNode->data;
            currNode = currNode->next;
        }

        return listAsString.str();
    }
};

#endif