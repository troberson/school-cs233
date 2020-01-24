#include "BSTInterface.h"
#include <string>

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
    Pair** root = new Pair*[size];

    /*
     * Prints the inorder the tree to the stream out
     *
     */
    void printTree(int index, std::ostream& out) const
    {
    }

  public:
    BinarySearchTree()
    {
        // add needed code
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
        // stub code remove
        return root == nullptr;
    }

    /*
     * Prints the inorder the tree to the stream out
     */
    void printTree(std::ostream& out = cout) const
    {
        printTree(0, out);
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
    bool insert(Value value, KeyComparable key)
    {

        return false;
    }

    /*
     * Removes the nodes if it contains the given item
     */
    void remove(const KeyComparable& key)
    {
    }

    int getSize()
    {
        return 0;
    }

    int getCount()
    {
        return 0;
    }
};