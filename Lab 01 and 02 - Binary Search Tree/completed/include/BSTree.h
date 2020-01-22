///
// Name: Tamara Roberson
// Section: A
// Program Name: Lab 02 - Binary Search Tree
//
// Description: An object-oriented implementation of a Binary Search Tree.
// Includes functions for inserting, finding, and removing nodes. The nodes
// are referenced by a key, which can be any comparable type.
///


#include "BSTInterface.h"
#include "ComputerScientist.h"

#include <string>

using namespace std;

template <typename KeyComparable, typename Value>
class BinarySearchTree : public BSTInterface<KeyComparable, Value>
{
  private:
    /*
     * Private BinaryNode Class
     */
    class BinaryNode
    {
      public:
        KeyComparable key;
        Value value;

        BinaryNode* left;
        BinaryNode* right;
        // Initialize class members from constructor arguments
        // by using a member initializer list.
        // This method uses direct initialization, which is more
        // efficient than using assignment operators inside the constructor
        // body.
        BinaryNode(KeyComparable& key, Value& value,
                   BinaryNode* left = nullptr, BinaryNode* right = nullptr)
            : value{value}, left{left}, right{right}, key{key}
        {
        }
    };

    // the root node of the tree
    BinaryNode* root = nullptr;

    /*
     * Inserts a node into the tree
     * returns true if item inserted
     * returns false if item not inserted (Key already in tree)
     * maintains this property of the tree:
     *     All nodes to the left will be less
     *     All nodes to the right will be greater
     */
    bool insert(Value item, KeyComparable key, BinaryNode* node)
    {
        // Check if the given node is null
        if (!node)
        {
            return false; // FAIL: node does not exist
        }

        // Check if the key is the same as the current key (already exists)
        if (key == node->key)
        {
            return false; // FAIL: key already exists
        }

        // Use left branch for smaller keys
        if (key < node->key)
        {
            // If there is a left node, recurse down the left branch
            if (node->left)
            {
                return insert(item, key, node->left);
            }

            // Otherwise, make this the left child
            node->left = new BinaryNode(key, item);
            return true; // SUCCESS: node added
        }

        // Use right branch for larger keys
        // If there is a right node, recurse down the right branch
        if (node->right)
        {
            return insert(item, key, node->right);
        }

        node->right = new BinaryNode(key, item);
        return true; // SUCCESS: node added
    }

    /*
     * remove a node from the tree
     * maintains this property of the tree:
     *     All nodes to the left will be less
     *     All nodes to the right will be greater
     */
    void remove(const KeyComparable& key, BinaryNode*& t)
    {
        // Check if the given node is null
        if (!t)
        {
            return; // FAIL: node does not exist
        }

        // Check left
        if (key < t->key)
        {
            return remove(key, t->left);
        }

        // Check right
        if (key > t->key)
        {
            return remove(key, t->right);
        }

        // Check current node
        if (key != t->key)
        {
            return; // FAIL: key not found
        }

        // Has a left child?
        if (t->left)
        {
            // Has a right child?
            if (t->right)
            {
                // Has two children
                // Replace the current node with the largest in the left
                // subtree by copying the key and value, keeping the
                // current left and right children.
                auto max = findMax(t->left);
                t->key = max->key;
                t->value = max->value;

                // Call this function on the key to delete to unlink
                // correctly from parent
                remove(max->key, t->left);
            }
            else
            {
                // Has a left child only.
                // Replace the current node with the left child.
                auto tmp = t->left;
                delete t;
                t = tmp;
            }
        }
        else if (t->right)
        {
            // Has a right child only
            // Replace the current node with the right child.
            auto tmp = t->right;
            delete t;
            t = tmp;
        }
        else
        {
            // No children
            // Just delete.
            delete t;
            t = nullptr;
            return; // Don't reset root if there's no children
        }

        // Reset root if deleted
        if (key == root->key)
        {
            root = t;
        }
    }

    /*
     * Finds the node with the smallest element in the subtree
     */
    BinaryNode* findMin(BinaryNode* t) const
    {
        // Check if node is null
        if (!t)
        {
            return nullptr; // FAIL: Node is null
        }

        // If there is a left child, keep walking
        if (t->left)
        {
            return findMin(t->left);
        }

        // If there is no left child, return the current node
        return t;
    }

    /*
     * Finds the node with the largest element in the subtree
     */
    BinaryNode* findMax(BinaryNode* t) const
    {
        // Check if node is null
        if (!t)
        {
            return nullptr; // FAIL: Node is null
        }

        // If there is a right child, keep walking
        if (t->right)
        {
            return findMax(t->right);
        }

        // If there is no right child, return the current node
        return t;
    }

    /*
     * Finds the node with that satisfies equality for the element
     */
    BinaryNode* find(const KeyComparable& key, BinaryNode* node) const
    {
        // Check if the given node is null
        if (!node)
        {
            return nullptr; // FAIL: node does not exist
        }

        // Check the current node
        if (key == node->key)
        {
            return node; // SUCCESS: found the desired node
        }

        // If the key is less than the current node, check left;
        // otherwise, check right.
        // Return either the located node or nullptr if not found
        return (key < node->key) ? find(key, node->left)
                                 : find(key, node->right);
    }

    /*
     * Returns true if the item is found in the tree
     */
    bool contains(const Value& item, BinaryNode* t) const
    {
        // optional code
        return false;
    }

    /*
     * Removes all elelements from the tree
     */
    void makeEmpty(BinaryNode*& t)
    {
        // optional code
    }

    /*
     * Prints the inorder the tree to the stream out
     */
    void printTree(BinaryNode* t, std::ostream& out) const
    {
        // Skip null nodes
        if (!t)
        {
            return;
        }

        // Print in-order, recursing down branches:
        //   Left Branch, Current, Right Branch
        printTree(t->left, out);
        out << *t->value << "\n";
        printTree(t->right, out);
    }

  public:
    BinarySearchTree()
    {
        // optional code
    }

    ~BinarySearchTree()
    {
        // optional code
    }

    /*
     * Finds the node with the smallest element in the tree
     */
    const Value findMin() const
    {
        BinaryNode* found = findMin(root);
        return found ? found->value : nullptr;
    }

    /*
     * Finds the node with the largest element in the tree
     */
    const Value findMax() const
    {
        BinaryNode* found = findMax(root);
        return found ? found->value : nullptr;
    }

    /*
     * Finds the node with that the key
     * updates the founditem refrerence if found
     * returns true if it was found
     * returns false if it was not
     */
    bool find(const KeyComparable& key, Value& founditem) const
    {
        // Try finding the key
        BinaryNode* foundNode = find(key, root);

        // If the key is found, set the out param 'founditem' to the value
        if (foundNode)
        {
            founditem = foundNode->value;
        }

        // Return true if the key was found, false otherwise
        return (foundNode != nullptr);
    }

    /*
     * Returns true if the item is found in the tree
     */
    bool contains(const KeyComparable& key) const
    {
        // optional code
        return false;
    }

    /*
     * Returns true if tree has no nodes
     */
    bool isEmpty() const
    {
        // optional code
        return root == nullptr;
    }

    /*
     * Prints the inorder the tree to the stream out
     */
    void printTree(std::ostream& out = cout) const
    {
        printTree(root, out);
    }

    /*
     * Removes all nodes from the tree
     */
    void makeEmpty()
    {
        // optional code
    }

    /*
     * Inserts a node into the tree
     * maintains this property of the tree:
     *     All nodes to the left will be less
     *     All nodes to the right will be greater
     */
    bool insert(Value value, KeyComparable key)
    {
        // If there is no root node, add this as the root
        if (!root)
        {
            root = new BinaryNode(key, value);
            return true;
        }

        // Try adding the value to the tree, starting from the root
        return insert(value, key, root);
    }

    /*
     * Removes the nodes if it contains the given item
     */
    void remove(const KeyComparable& key) override
    {
        remove(key, root);
    }
}; // end of BinarySearchTree class
