///
// Name: Tamara Roberson
// Section: A
// Program Name: Lab 01 - Binary Search Tree
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
    void remove(const KeyComparable& key, BinaryNode** t)
    {
        // TODO write for lab 2
    }

    /*
     * Finds the node with the smallest element in the subtree
     */
    BinaryNode* findMin(BinaryNode* t) const
    {
        // TODO write for lab 2
    }

    /*
     * Finds the node with the largest element in the subtree
     */
    BinaryNode* findMax(BinaryNode* t) const
    {
        // TODO write for lab 2
    }

    /*
     * Finds the node with that satisfies equality for the element
     */
    BinaryNode* find(const KeyComparable& key, BinaryNode* node) const
    {
        // TODO write for lab 1
        return nullptr;
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
        // TODO calls private findMin  lab 2
        return nullptr;
    }

    /*
     * Finds the node with the largest element in the tree
     */
    const Value findMax() const
    {
        // TODO calls private findMax  lab 2
        return nullptr;
    }

    /*
     * Finds the node with that the key
     * updates the founditem refrerence if found
     * returns true if it was found
     * returns false if it was not
     */
    bool find(const KeyComparable& key, Value& founditem) const
    {
        // TODO calls private find lab 1
        return false;
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
        // TODO Calls the private printTree function
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
    void remove(const KeyComparable& key)
    {
        // TODO calls private remove
    }

}; // end of BinarySearchTree class
