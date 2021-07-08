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
        Node(const T &data, Node *next) : data(data), next(next) {}
    };
    Node *head;

public:
    LinkedList() : LinkedListInterface<T>(), head(NULL) {}
    ~LinkedList() {}

    void push_front(const T &value)
    {
        std::cout << "Push front" << std::endl;
        head = new Node(value, head);
        return;
    }

    void pop_front(void)
    {
        std::cout << "Pop front" << std::endl;
    }

    T &front(void)
    {
        std::cout << "Front" << std::endl;
        T tVar;
        return tVar;
    }

    bool empty(void) const
    {
        std::cout << "Empty" << std::endl;
        return true;
    }

    void remove(const T &value)
    {
        std::cout << "Remove" << std::endl;
    }

    void clear(void)
    {
        std::cout << "Clear" << std::endl;
    }

    void reverse(void)
    {
        std::cout << "Reverse" << std::endl;
    }

    size_t size(void) const
    {
        std::cout << "Size" << std::endl;
        return 1;
    }

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