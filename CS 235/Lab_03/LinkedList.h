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
        Node(const T &data, Node *next = nullptr) : data(data), next(next) {}
    };
    Node *head;

public:
    LinkedList() : LinkedListInterface<T>(), head(nullptr) {}
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
    void pop_front(void);

    /**
     * Get the first element in the list. Throws a string error message if list is empty
     * @return the first element in the list
     */
    T &front(void)
    {
        std::cout << "Front" << std::endl;
        if (head == nullptr)
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
        bool temp = (head == nullptr); //FIXME delete
        return (head == nullptr);
    }

    /**
     * Find value and remove it.
     * @param value the value to be removed
     * @return void
     */
    void remove(const T &value);

    /**
     * Delete the list
     * @return void
     */
    void clear(void)
    {
        std::cout << "Clear" << std::endl;
        Node *currNode = head;
        while (currNode != nullptr)
        {
            Node *nextNode = currNode->next;
            delete currNode;
            currNode = nextNode;
        }
        head = nullptr;
    }

    /**
     * Reverse the order of the list. Throws a string error message if list is empty
     * @return void
     */
    void reverse(void);

    /**
     * Get the size of the list
     * @return the size of the list as a size_t
     */
    size_t size(void) const
    {
        std::cout << "Size" << std::endl;
        size_t nodeCount = 0;
        Node *currPointer = head;
        while (currPointer != nullptr)
        {
            nodeCount++;
            currPointer = currPointer->next;
        }
        return nodeCount;
    }

    /**
     * Get the contents of the list as a string
     * @return the contents of the list as a string
     */
    std::string toString(void) const;
};

template <typename T>
void LinkedList<T>::pop_front(void)
{
    std::cout << "Pop front" << std::endl;
    if (head == nullptr) // If list is empty
    {
        std::string errMsg = "Empty!";
        throw errMsg;
    }

    if (head->next == nullptr) // If list is only 1 node long
    {
        delete head;
        head = nullptr;
        return;
    }

    // Otherwise
    Node *newHead = head->next;
    delete head;
    head = newHead;
    return;
}

template <typename T>
void LinkedList<T>::remove(const T &value) // FIXME move out of class definition
{
    std::cout << "Remove" << std::endl;
    Node *currNode = head;
    Node *prevNode = nullptr;
    while (currNode != nullptr)
    {
        if (currNode->data == value)
        {
            if (prevNode == nullptr) // If the first node, set the next node to head and delete the current node
            {
                head = currNode->next;
                delete currNode;
                currNode = head;
                continue;
            }
            else // Otherwise, set the previous node to point to the next node and delete it
            {
                prevNode->next = currNode->next;
                delete currNode;
                currNode = prevNode->next;
                continue;
            }
        }

        //If it's not a match, increment currNode and prevNode;
        prevNode = currNode;
        currNode = currNode->next;
    }
}

template <typename T>
void LinkedList<T>::reverse(void)
{
    std::cout << "Reverse" << std::endl;
    if (head == nullptr) // If list is empty
    {
        std::string errMsg = "Empty!";
        throw errMsg;
    }

    if (head->next == nullptr) // If list is only one item
    {
        return;
    }

    // Reverse the array
    Node *initialHead = head;
    // Node *prevNode = head;
    Node *ptrToMove = initialHead->next;

    // Move the first node (while loop assumes head has been moved)
    initialHead->next = ptrToMove->next;
    ptrToMove->next = head;
    head = ptrToMove;

    while (initialHead->next != nullptr)
    {
        // prevNode = head;
        // while (prevNode->next != initialHead) // Loop until prevNode is right before the initial head
        // {
        //     prevNode = prevNode->next;
        // }
        Node *ptrToMove = initialHead->next;
        initialHead->next = ptrToMove->next;
        ptrToMove->next = head;
        head = ptrToMove;

        // prevNode->next = nullptr; // Make the previous node the new final node
        // lastNode->next = head;    // Make the last node point to the old first node
        // head = lastNode;          // Make the last node the new first node;
    }
}

template <typename T>
std::string LinkedList<T>::toString(void) const
{
    std::cout << "To String" << std::endl;
    std::ostringstream listAsString("");

    Node *currNode = head;
    while (currNode != nullptr)
    {
        listAsString << " " << currNode->data;
        currNode = currNode->next;
    }

    if (head == nullptr)
    {
        listAsString << " Empty!";
    }

    return listAsString.str();
}

#endif