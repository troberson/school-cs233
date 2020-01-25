#include "BSTInterface.h"
#include <string>
#include <type_traits>

using namespace std;
template <typename KeyComparable, typename Value>
class BinarySearchTree : BSTInterface<KeyComparable, Value>
{
  private:
    /*
     * Private Node Class
     *
     */
    class Pair
    {
      public:
        KeyComparable key;
        Value value;

        // Initialize class members from constructor arguments
        // by using a member initializer list.
        // This method uses direct initialization, which is more
        // efficient than using assignment operators inside the constructor
        // body.
        Pair(KeyComparable& key, Value& value) : value{value}, key{key}
        {
        }
    };

    // number of values stored in the tree
    int count = 0;
    // capacity of array holding the tree
    int size = 25;
    // the array that holds the pairs
    Pair** root = new Pair*[size]();

    /*
     * Returns the same index given if valid or 0 if invalid.
     */
    [[nodiscard]] int getIndex(int idx) const
    {
        return (idx < 1 || idx >= size) ? 0 : idx;
    }

    /*
     * Returns the index of the left child of an index or 0 if no
     * left child exists
     */
    [[nodiscard]] int getLeft(int idx) const
    {
        return getIndex(2 * idx);
    }

    /*
     * Returns the index of the right child of an index or 0 if no
     * right child exists
     */
    [[nodiscard]] int getRight(int idx) const
    {
        return getIndex(2 * idx + 1);
    }

    /*
     * Returns the index of the parent of an index or 0 if node is root or
     * invalid
     */
    [[nodiscard]] int getParent(int idx) const
    {
        if (idx <= 1)
        {
            return 0;
        }

        return getIndex(idx / 2);
    }

    /*
     * Prints the inorder the tree to the stream out
     *
     */
    void printTree(int index, std::ostream& out) const
    {
        if (getIndex(index) == 0 || !root[index])
        {
            return; // FAIL: no such node
        }

        // out << "DEBUG: Print Left (" << index << ")\n";
        printTree(getLeft(index), out);
        // out << "DEBUG: Current: ";
        out << *root[index]->value << "\n";
        // out << "DEBUG: Print Right (" << index << ")\n";
        printTree(getRight(index), out);
    }

    /*
     * Inserts the given key-value pair into the tree in sorted order below
     * the given index. Returns true if added, false if not added.
     */
    bool insert(KeyComparable key, Value& value, int index)
    {
        // cout << "Inserting Key " << key << " below Index " << index
        //      << "\n";

        // TODO: Update to grow array as needed
        if (getIndex(index) == 0)
        {
            return false; // FAIL: Invalid index
        }

        Pair*& curNode = this->root[index];

        // If current index is empty, put the new node there
        if (curNode == nullptr)
        {
            // cout << "Current Node is empty, adding key " << key << "\n";
            curNode = new Pair(key, value);
            this->count++;
            return true; // SUCCESS: Key added
        }

        // cout << "Current Node has Key " << curNode->key << "\n";

        // Check if the key is the same as the current key (already exists)
        if (key == curNode->key)
        {
            return false; // FAIL: Key already exists
        }

        // Use left branch for smaller keys
        if (key < curNode->key)
        {
            return insert(key, value, getLeft(index));
        }

        // Use right branch for larger keys
        return insert(key, value, getRight(index));
    }


  public:
    BinarySearchTree()
    {
    }

    ~BinarySearchTree()
    {
        // add needed code
    }

    /*
     * Finds the node with the smallest element in the tree
     */
    const Value findMin() const
    {
        // stub code remove
        return nullptr;
    }

    /*
     * Finds the node with the largest element in the tree
     */
    const Value findMax() const
    {
        // stub code remove
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

        return false;
    }

    /*
     * Returns true if the item is found in the tree
     */
    bool contains(const KeyComparable& key) const
    {
        // stub code remove
        return false;
    }

    /*
     * Returns true if tree has no nodes
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /*
     * Prints the inorder the tree to the stream out
     */
    void printTree(std::ostream& out = cout) const
    {
        printTree(1, out);
    }

    /*
     * Removes all nodes from the tree
     */
    void makeEmpty()
    {
    }

    /*
     * Inserts a node into the tree
     * maintains this property of the tree:
     *     All nodes to the left will be less
     *     All nodes to the right will be greater
     */
    bool insert(Value value, KeyComparable key) override
    {
        return insert(key, value, 1);
    }

    /*
     * Removes the nodes if it contains the given item
     */
    void remove(const KeyComparable& key)
    {
    }

    int getSize()
    {
        return this->size;
    }

    int getCount()
    {
        return this->count;
    }
};