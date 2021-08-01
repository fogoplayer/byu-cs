#ifndef BST_H
#define BST_H
#include <string>
#include <utility>
#include <functional>

#include "sstream"

#include "BSTInterface.h"

/** A binary tree container */
template <typename T>
class Bst : public BSTInterface<T>
{
private:
    /** A binary tree node with data, left and right child pointers */
    struct Node
    {
        Node(T data, Node *left = nullptr, Node *right = nullptr) : data(data), left(left), right(right) {}
        Node(Node &other)
        {
            this->data = other.data;
            if (other.left != nullptr)
            {
                this->left = other.left;
            }
            else
            {
                this->left = nullptr;
            }

            if (other.right != nullptr)
            {
                this->right = other.right;
            }
            else
            {
                this->right = nullptr;
            }
        }

        ~Node()
        {
            if (left != nullptr)
            {
                delete left;
                left = nullptr;
            }
            if (right != nullptr)
            {
                delete right;
                right = nullptr;
            }
        }

        T data;
        Node *left;
        Node *right;

        /**
         * Return a string of the subtree where node is the root
         */
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

        /**
         * Overload the insertion operator
         * @return an ostream with the contents of the subtree
         */
        friend std::ostream &operator<<(std::ostream &os, Node &node)
        {
            os << node.toString();
            return os;
        }

        /**
         * Overload the assignment operator
         * @return an a copy of the node with the contents of the subtree
         */
        Node &operator=(Node &other)
        {
            this = Node(other);
        }
    };

    Node *root;

    /** Output nodes at a given level */
    bool outLevel(Node *root, int level, std::ostringstream &out) const;

    /**
     * Recursive size function
     * @param root a pointer to a Node
     * @return size of the subtree at root
     */
    int size(Node *root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        int leftSize = root->left != nullptr ? size(root->left) : 0;
        int rightSize = root->right != nullptr ? size(root->right) : 0;
        return 1 + leftSize + rightSize;
    }

    /**
     * Recursive find function
     * @param value the value to remove
     * @param root a pointer to a Node
     * @return "found" or "not found"
     */
    std::string find(T &value, Node *root);

    /**
     * Recursive remove function
     * @param value the value to remove
     * @param roote a pointer to a Node 
     * @return true if successful, false if not
     */
    bool removeNode(const T &value, Node *&root);

    /**
     * Get the inorder precessor (1L, then R)
     * @param root the node to find the precessor of
     * @return a pointer to the node
     */
    Node *getInOrderPredecessor(Node *root)
    {
        Node *predecessor = root->left;
        while (predecessor->right != nullptr)
        {
            predecessor = predecessor->right;
        }
        return predecessor;
    }

    // TODO check const-ness

public:
    Bst(void) : root(nullptr){};
    ~Bst(void)
    {
        delete root;
    }

    /**
     * Return true if node added to BST, else false
     */
    virtual bool addNode(const T &value);

    /**
     * Return true if node removed from BST, else false
     */
    virtual bool removeNode(const T &value)
    {
        return removeNode(value, root);
    }

    /**
     * Return the number of nodes in the tree
     */
    int size()
    {
        return size(root);
    }

    /**
     * Whether or not if a value is in the tree
     * @param value the value to search for
     * @return "found" if it's in the tree, "found" if it's not
     */
    std::string find(T &value)
    {
        return find(value, root);
    }

    /**
     * Return true if BST cleared of all nodes, else false
     */
    virtual bool clearTree()
    {
        delete root;
        root = nullptr;
        return true;
    }

    /**
     * Return a level order traversal of a BST as a string
     */
    virtual std::string toString() const;

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

template <typename T>
bool Bst<T>::outLevel(Bst<T>::Node *root, int level, std::ostringstream &out) const
{
    if (root == nullptr)
    {
        return false;
    }

    if (level == 0)
    {

        out << " " << root->data;

        if ((root->left != nullptr) || (root->right != nullptr))
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

template <typename T>
std::string Bst<T>::find(T &value, Bst<T>::Node *root)
{
    if (root == nullptr)
    {
        return "not found";
    }
    else if (root->data == value ||
             find(value, root->left) == "found" ||
             find(value, root->right) == "found")
    {
        return "found";
    }
    else
    {
        return "not found";
    }
}

template <typename T>
bool Bst<T>::removeNode(const T &value, Bst<T>::Node *&root)
{
    // if node is nullptr , return false
    if (root == nullptr)
    {
        return false;
    }

    // if value < node->data, return removeNode(value, node->left)
    else if (value < root->data)
    {
        return removeNode(value, root->left);
    }

    // if node->data < value, return removeNode(value, node->right)
    else if (root->data < value)
    {
        return removeNode(value, root->right);
    }

    // If code reaches this point, must be a match \\

    // if node has no children, parent = nullptr , return true
    if (root->left == nullptr && root->right == nullptr)
    {
        delete root;
        root = nullptr;
        return true;
    }

    // if node has 1 child, parent = node->(left or right), return true
    if (root->left != nullptr && root->right == nullptr)
    {
        Node *newRoot = new Node(*root->left);
        delete root;
        root = newRoot;
        return true;
    }
    else if (root->left == nullptr && root->right != nullptr)
    {
        Node *newRoot = new Node(*root->right);
        delete root;
        root = newRoot;
        return true;
    }

    // exchange node->data with in_order_predecessor->data
    Node *predecessor = getInOrderPredecessor(root);
    std::swap(root->data, predecessor->data);
    removeNode(predecessor->data, root->left);
    return true;
}

template <typename T>
bool Bst<T>::addNode(const T &value)
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

template <typename T>
std::string Bst<T>::toString() const
{
    if (root == nullptr)
    {
        std::string errMsg = " empty";
        return errMsg;
    }

    std::ostringstream os;
    os << std::endl;

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

#endif // BST_INTERFACE_H
