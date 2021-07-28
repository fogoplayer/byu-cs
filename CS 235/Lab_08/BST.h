#ifndef BST_H
#define BST_H
#include <string>
#include "sstream"

#include "BSTInterface.h"

/** A binary tree node with data, left and right child pointers */
template <typename T>
class Bst : public BSTInterface<T>
{
private:
    struct Node
    {
        Node(data, left = nullptr, right = nullptr) : data(data), left(left), right(right){};
        ~Node()
        {
            delete left;
            delete right;
        }

        T data;
        Bst *left;
        Bst *right;
    };

    Node root;

public:
    Bst(void){};
    virtual ~Bst(void){};

    /**
     * Return true if node added to BST, else false
     */
    virtual bool addNode(const T &)
    {
        return true;
    }

    /**
     * Return true if node removed from BST, else false
     */
    virtual bool removeNode(const T &)
    {
        return true;
    }

    /**
     * Return true if BST cleared of all nodes, else false
     */
    virtual bool clearTree()
    {
        return true;
    }

    /**
     * Return a level order traversal of a BST as a string
     */
    virtual std::string toString() const
    {
        std::ostringstream os;
        return os.str();
    }

    /**
     * Overload the insertion operator
     * @return an ostream with the contents of all private data members
     */
    friend std::ostream &operator<<(std::ostream &os, Bst &bst)
    {
        os << bst.toString();
        return os;
    }
};
#endif // BST_INTERFACE_H
