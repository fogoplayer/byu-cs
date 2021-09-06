#ifndef BST_H
#define BST_H
#include <string>
#include <functional>

#include "sstream"

/** A binary tree container */
template <typename T>
class Bst
{
private:
    /** A binary tree node with data, left and right child pointers */
    struct Node
    {
        Node(T data, Node *left = nullptr, Node *right = nullptr) : data(data), left(left), right(right) {}
        ~Node()
        {
            delete left;
            left = nullptr;
            delete right;
            right = nullptr;
        }

        T data;
        int depth;
        Node *left;
        Node *right;

        /** Tostring function for Node */
        std::string toString() const;

        /**
         * Overload the insertion operator
         * @return an ostream with the contents of the node
         */
        friend std::ostream &operator<<(std::ostream &os, Node &node)
        {
            os << node.toString();
            return os;
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
    int size(Node *root) const;

    /**
     * Recursive find function
     * @param root a pointer to a Node
     * @return "found" or "not found"
     */
    std::string find(const T &value, Node *root) const;

    /**
     * Recursive inorder traversal of a BST as a string
     */
    virtual std::string toString(Node *node) const
    {
        if (node)
        {
            /* code */
        }

        std::ostringstream os;
        std::string leftSide = node->left != nullptr ? toString(node->left) : "";
        std::string rightSide = node->right != nullptr ? toString(node->right) : "";
        os << leftSide << "," << node->data << rightSide;
        return os.str();
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
    virtual bool addNode(const T &value);

    /**
     * Return the number of nodes in the tree
     */
    int size() const
    {
        return size(root);
    }

    /**
     * Whether or not if a value is in the tree
     * @param value the value to search for
     * @return "found" if it's in the tree, "found" if it's not
     */
    std::string find(const T &value) const
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
     * Return an inorder traversal of a BST as a string
     */
    virtual std::string toString() const
    {
        if (root == nullptr)
        {
            std::string errMsg = " empty";
            return errMsg;
        }

        return toString(root).substr(1);
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

template <typename T>
std::string Bst<T>::Node::toString() const
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

template <typename T>
bool Bst<T>::outLevel(Bst<T>::Node *root, int level, std::ostringstream &out) const
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

template <typename T>
int Bst<T>::size(Node *root) const
{
    if (root == nullptr)
    {
        return 0;
    }
    int leftSize = root->left != nullptr ? size(root->left) : 0;
    int rightSize = root->right != nullptr ? size(root->right) : 0;
    return 1 + leftSize + rightSize;
}

template <typename T>
std::string Bst<T>::find(const T &value, Node *root) const
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
            if (std::less<T>{}(value, currNode->data))
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

#endif