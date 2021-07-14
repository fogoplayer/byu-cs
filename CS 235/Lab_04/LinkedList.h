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

    class Iterator
    {
    private:
        Node *iNode;

    public:
        Iterator(Node *head) : iNode(head) {}
        ~Iterator() {}

        /**
         * Determine if two Iterators are pointing to the same object
         * @param rhs an Iterator object to compare to the current Iterator object
         * @return a boolean sharing if they are equal
         */
        bool operator!=(const Iterator &rhs) const
        {
            return this->iNode != rhs.iNode;
        }

        /**
         * Determine if two Iterators are pointing to the same object
         * @param rhs an Iterator object to compare to the current Iterator object
         * @return a boolean sharing if they are equal
         */
        bool operator==(const Iterator &rhs) const
        {
            return this->iNode == rhs.iNode;
        }

        /**
         * Preincrement operator
         * @return an Iterator pointing to the next element in the list
         */
        Iterator &operator++()
        {
            iNode = iNode->next;
            return *this;
        }

        /**
         * Dereference operator
         * @return the data value of the node pointed to by the Iterator)
         */
        T &operator*() const
        {
            return iNode->data;
        }

        /**
         * Get the next value for the node the iterator is pointing to
         * @return a pointer to a node
         */
        Node *getNext() const
        {
            return iNode->next;
        }

        /**
         * Change the next value for the node the iterator is pointing to
         * @param nodePtr a pointer to a node;
         */
        void setNext(Node *nodePtr)
        {
            iNode->next = nodePtr;
        }

        /**
         * Delete the node the Iterator is pointing to
         * @return an interator pointing to the node following the deleted node
         */
        Iterator deleteNode()
        {
            Node *returnVal = iNode->next;
            delete iNode;
            return Iterator(returnVal);
        }

        /**
         * Return the data in the iterator as a string
         * @return a string
         */
        std::string toString()
        {
            std::stringstream s;
            s << iNode.data;
            return s.str();
        }

        /**
         * @return an ostream with the data pointed to by the iterator
         */
        friend std::ostream &operator<<(std::ostream &os, Iterator &Iterator)
        {
            os << Iterator.toString();
            return os;
        }
    };

    /** Return iterator pointing to the first value in linked list */
    Iterator begin(void) const
    {
        return LinkedList<T>::Iterator(head);
    }

    /** Return iterator pointing to something not in linked list */
    Iterator end(void) const
    {
        return LinkedList<T>::Iterator(NULL);
    }

    /** Return iterator pointing found value in linked list */
    Iterator find(Iterator first, Iterator last, const T &value) const
    {
        // Go through each element between first and last and check its value against the argument
        Iterator searchPosition(first);
        while (searchPosition != last)
        {
            if (*searchPosition == value)
            {
                break;
            }
            ++searchPosition;
        }

        // If search went beyond the list, value wasn't in there
        if (searchPosition == last)
        {
            std::string errMsg = " Not Found";
            throw errMsg;
        }
        return searchPosition;
    }

    /** Return iterator pointing to inserted value in linked list */
    Iterator insert(Iterator Position, const T &value);

    /** Return iterator pointing to inserted value in linked list */
    Iterator insert_after(Iterator Position, const T &value);

    /** Return iterator pointing to next item after deleted node linked list */
    Iterator erase(Iterator Position);

    /** Replace first found old_value(s) with new_value */
    void replace(Iterator First, Iterator Last, const T &old_value, const T &new_value)
    {
        while (First != Last)
        {
            if (*First == old_value)
            {
                *First = new_value;
            }
            ++First;
        }
        return;
    }

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
        Node *CurrNode = head;
        while (CurrNode != nullptr)
        {
            Node *nextNode = CurrNode->next;
            delete CurrNode;
            CurrNode = nextNode;
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

    /**
     * @return an ostream with the contents of all private data members
    **/
    friend std::ostream &operator<<(std::ostream &os, LinkedList<T> &list)
    {
        os << list.toString();
        return os;
    }
};

template <typename T>
LinkedList<T>::Iterator LinkedList<T>::insert(Iterator Position, const T &value)
{
    if (Position == Iterator(nullptr))
    {
        std::string errMsg = " Not Found";
        throw errMsg;
    }

    if (Position.getNext() == head->next) // Special case--first elem is match
    {
        Node *newNode = new Node(value, head);
        head = newNode;
        return Iterator(newNode);
    }

    // Check all other elems for match
    Node *beforePosition = head;
    while (beforePosition->next != nullptr)
    {
        if (beforePosition->next->data == *Position &&        // If they point to the same data
            beforePosition->next->next == Position.getNext()) // And the same next value
        {
            break;
        }
        beforePosition = beforePosition->next;
    }

    Node *newNode = new Node(value, beforePosition->next);
    beforePosition->next = newNode;
    return Iterator(newNode);
}

template <typename T>
LinkedList<T>::Iterator LinkedList<T>::insert_after(Iterator Position, const T &value)
{
    if (Position == Iterator(nullptr))
    {
        std::string errMsg = " Not Found";
        throw errMsg;
    }

    Node *newNode = new Node(value, Position.getNext());
    Position.setNext(newNode);
    return newNode;
}

template <typename T>
LinkedList<T>::Iterator LinkedList<T>::erase(Iterator Position)
{
    if (Position == Iterator(nullptr))
    {
        std::string errMsg = " Not Found";
        throw errMsg;
    }

    // Loop through and find Position (CurrNode) and the node before Position (PrevNode)
    Node *CurrNode = head;
    Node *PrevNode = nullptr;
    while (CurrNode != nullptr)
    {
        if ((CurrNode->data == *Position) &&        // If they point to the same data
            (CurrNode->next == Position.getNext())) // And to the same next value
        {
            break; // Escape once a match is found
        }
        PrevNode = CurrNode;
        CurrNode = CurrNode->next;
    }

    if (PrevNode == nullptr)
    {
        head = Position.getNext();
        Position.deleteNode();
        return head;
    }
    else
    {
        PrevNode->next = Position.getNext();
        Position.deleteNode();
        return PrevNode->next;
    }
}

template <typename T>
void LinkedList<T>::replace(Iterator First, Iterator Last, const T &old_value, const T &new_value)
{
    while (First != Last)
    {
        if (*First == old_value)
        {
            *First = new_value;
        }
        ++First;
    }
    return;
}

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
void LinkedList<T>::remove(const T &value)
{
    std::cout << "Remove" << std::endl;
    Node *CurrNode = head;
    Node *PrevNode = nullptr;
    while (CurrNode != nullptr)
    {
        if (CurrNode->data == value)
        {
            if (PrevNode == nullptr) // If the first node, set the next node to head and delete the current node
            {
                head = CurrNode->next;
                delete CurrNode;
                CurrNode = head;
                continue;
            }
            else // Otherwise, set the previous node to point to the next node and delete it
            {
                PrevNode->next = CurrNode->next;
                delete CurrNode;
                CurrNode = PrevNode->next;
                continue;
            }
        }

        //If it's not a match, increment CurrNode and PrevNode;
        PrevNode = CurrNode;
        CurrNode = CurrNode->next;
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
    // Node *PrevNode = head;
    Node *ptrToMove = initialHead->next;

    // Move the first node (while loop assumes head has been moved)
    initialHead->next = ptrToMove->next;
    ptrToMove->next = head;
    head = ptrToMove;

    while (initialHead->next != nullptr)
    {
        // PrevNode = head;
        // while (PrevNode->next != initialHead) // Loop until PrevNode is right before the initial head
        // {
        //     PrevNode = PrevNode->next;
        // }
        Node *ptrToMove = initialHead->next;
        initialHead->next = ptrToMove->next;
        ptrToMove->next = head;
        head = ptrToMove;

        // PrevNode->next = nullptr; // Make the previous node the new final node
        // lastNode->next = head;    // Make the last node point to the old first node
        // head = lastNode;          // Make the last node the new first node;
    }
}

template <typename T>
std::string LinkedList<T>::toString(void) const
{
    std::cout << "To String" << std::endl;
    std::ostringstream listAsString("");

    Node *CurrNode = head;
    while (CurrNode != nullptr)
    {
        listAsString << " " << CurrNode->data;
        CurrNode = CurrNode->next;
    }

    if (head == nullptr)
    {
        listAsString << " Empty!";
    }

    return listAsString.str();
}

#endif