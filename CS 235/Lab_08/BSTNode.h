#ifndef BST_INTERFACE_H
#define BST_INTERFACE_H
#include <string>

/** A binary tree node with data, left and right child pointers */
template <typename T>
class BSTNode
{
private:
    T data;
    BSTNode *left;
    BSTNode *right;

public:
    BSTNode(void) {}
    virtual ~BSTNode(void) {}

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
    friend std::ostream &operator<<(std::ostream &os, ParentClass &Obj)
    {
        os << Obj.toString();
        return os;
    }
};
#endif // BST_INTERFACE_H
