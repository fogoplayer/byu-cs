#ifndef BST_H
#define BST_H
#include <string>
#include <functional>

#include "sstream"

#include "BSTInterface.h"

/** A binary tree node with data, left and right child pointers */
template <typename T>
class Bst : public BSTInterface<T>
{
private:
    struct Node
    {
        Node(T data, Node *left = nullptr, Node *right = nullptr) : data(data), left(left), right(right) {}
        ~Node()
        {
            delete left;
            delete right;
        }

        T data;
        int depth;
        Node *left;
        Node *right;

        std::string toString()
        {
            std::ostringstream os;
            os << data << " ";
            if (left)
            {
                os << left->toString() << " ";
            }
            if (right)
            {
                os << right->toString() << " ";
            }

            return os.str();
        }
    };

    Node *root;

    /** Output nodes at a given level */
    bool outLevel(Node *root, int level, std::ostringstream &out) const
    {
        if (root == NULL)
            return false;

        if (level == 0)

        {

            out << " " << root->data;

            if ((root->left != NULL) || (root->right != NULL))
                return true;

            return false;
        }

        if ((level == 1) && !root->left && root->right)
            out << " _";

        bool left = outLevel(root->left, level - 1, out);

        bool right = outLevel(root->right, level - 1, out);

        if ((level == 1) && root->left && !root->right)
            out << " _";
        return left || right;
    }

public:
    Bst(void) : root(nullptr){};
    ~Bst(void)
    {
        delete root;
    }

    /**
     * Return true if node added to BST, else false
     */
    virtual bool addNode(const T &value)
    {
        if (root == nullptr)
        {
            this->root = new Node(value);
        }
        else
        {
            Node *currNode = root;
            bool nodePlaced = false;
            while (!nodePlaced)
            {
                // Left side
                if (std::less<T>{}(value, currNode->data)) // FIXME overload comparisons for strings and ints
                {
                    if (currNode->left == nullptr)
                    {
                        currNode->left = new Node(value);
                        nodePlaced = true;
                    }
                    else
                    {
                        currNode = currNode->left;
                    }
                }
                // Right side
                else if (std::less<T>{}(currNode->data, value))
                {
                    if (currNode->right == nullptr)
                    {
                        currNode->right = new Node(value);
                        nodePlaced = true;
                    }
                    else
                    {
                        currNode = currNode->right;
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
        size_t layer = 0;
        os << "  " << layer + 1 << ":";

        while (outLevel(root, layer, os))
        {
            os << std::endl;
            ++layer;
            os << "  " << layer + 1 << ":";
        }
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
