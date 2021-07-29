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
        ~Node() = default;

        T data;
        Node *left;
        Node *right;
    };

    Node *root;

public:
    Bst(void) : root(nullptr){};
    virtual ~Bst(void)
    {
        delete root[];
    }

    /**
     * Return true if node added to BST, else false
     */
    virtual bool addNode(const T &value)
    {
        if (root = nullptr)
        {
            root = new Node(value);
        }
        else
        {
            Node &currNode = *root;
            bool nodePlaced = false;
            while (!nodePlaced)
            {
                // Left side
                if (currNode > value) // FIXME overload comparisons for strings and ints
                {
                    if (currNode.left == nullptr)
                    {
                        currNode.left == Node(value);
                    }
                    else
                    {
                        currNode == *currNode.left;
                    }
                }
                // Right side
                else if (currNode > value)
                {
                    if (currNode.right == nullptr)
                    {
                        currNode.right == Node(value);
                    }
                    else
                    {
                        currNode == *currNode.right;
                    }
                }

                // Match
                else
                {
                    return false;
                }
            }
        }

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
