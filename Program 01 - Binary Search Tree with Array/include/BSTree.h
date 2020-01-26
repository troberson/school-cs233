#include "BSTInterface.h"

#include <algorithm>
#include <iterator>
#include <optional>
#include <string>
#include <utility>
#include <vector>

using namespace std;
template <typename KeyComparable, typename Value>
class BinarySearchTree : BSTInterface<KeyComparable, Value>
{
  public:
    static const size_t DEFAULT_SIZE = 25;

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
        // efficient than using assignment operators inside the
        // constructor body.
        Pair(KeyComparable& key, Value& value) : value{value}, key{key}
        {
        }
    };

    // number of values stored in the tree
    int count = 0;

    // capacity of array holding the tree
    int size = DEFAULT_SIZE;

    // the array that holds the pairs
    Pair** root = new Pair*[size]();

    /*
     * Returns the index of the left child of a given index.
     */
    [[nodiscard]] static int getLeft(int idx)
    {
        return 2 * idx;
    }

    /*
     * Returns the index of the right child of a given index.
     */
    [[nodiscard]] static int getRight(int idx)
    {
        return 2 * idx + 1;
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

        return idx / 2;
    }

    /*
     * Prints the inorder the tree to the stream out
     *
     */
    void printTree(int index, std::ostream& out) const
    {
        if (index <= 0 || index >= this->size)
        {
            // std::cout << "DEBUG: Invalid Index " << index << " Size is "
            //           << this->size << "\n";
            return; // FAIL: no such node
        }

        if (!this->root[index])
        {
            // std::cout << "DEBUG: Empty Index " << index << "\n";
            return; // FAIL: this node is empty
        }

        // out << "DEBUG: Print Left (" << index << ")\n";
        printTree(getLeft(index), out);
        // out << "DEBUG: Current (" << index << "): " ;
        out << *root[index]->value << "\n";
        // out << "DEBUG: Print Right (" << index << ")\n";
        printTree(getRight(index), out);
    }

    /*
     * Grow array to a larger size
     */
    void grow(size_t newSize = 0)
    {
        // default new size is double the current size plus one
        if (newSize <= 0)
        {
            newSize = 2 * this->size + 1;
        }

        // check if we actually need to grow
        if (newSize <= this->size)
        {
            return; // RETURN: no need to grow
        }

        // create a new array and copy the data from the current array into
        // it
        auto newRoot = new Pair*[newSize]();
        std::copy(this->root, this->root + this->size, newRoot);

        // update the object properties
        delete[] this->root;
        this->root = newRoot;
        this->size = newSize;
    }

    /*
     * Inserts the given key-value pair into the tree in sorted order
     * below the given index. Returns true if added, false if not
     * added.
     */
    bool insert(KeyComparable key, Value& value, int index)
    {
        // cout << "Inserting Key " << key << " below Index " << index
        //      << "\n";

        if (index <= 0)
        {
            return false; // FAIL: Invalid index
        }

        // Expand the capacity as needed
        // Note, this requires copying the whole array, so could be slow.
        if (index >= this->size)
        {
            // cout << "Current array size is " << this->size
            //      << ", growing to " << index << "\n";
            grow(index + 1);
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

    /*
     * Returns the pair at the last valid index returned by WalkFunction
     */
    template <typename WalkFunction>
    [[nodiscard]] Pair* findWhile(int index, WalkFunction walk) const
    {
        if (index < 1 || !this->root[index])
        {
            return nullptr; // FAIL: Index is invalid.
        }

        for (int newIndex = index;
             newIndex > 0 && newIndex < this->size && this->root[newIndex];
             newIndex = walk(index))
        {
            index = newIndex;
        }

        return this->root[index];
    }

    /*
     * Finds the node with the smallest element below the give index
     */
    [[nodiscard]] Value findMin(int index) const
    {
        auto node = findWhile(index, getLeft);
        return node ? node->value : nullptr;
    }

    /*
     * Finds the node with the largest element below the give index
     */
    [[nodiscard]] Value findMax(int index) const
    {
        auto node = findWhile(index, getRight);
        return node ? node->value : nullptr;
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
    [[nodiscard]] const Value findMin() const override
    {
        return findMin(1);
    }

    /*
     * Finds the node with the largest element in the tree
     */
    [[nodiscard]] const Value findMax() const override
    {
        return findMax(1);
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

    /*
     * Print the backing array in order as [index: key, value] for
     * debugging purposes.
     */
    void printArray(std::ostream& out = cout) const
    {
        out << "Array of size " << this->size << " storing " << this->count
            << " values.\n";

        for (int i = 1; i < this->size; i++)
        {
            out << "[" << i << ": ";
            auto node = this->root[i];
            if (node)
            {
                out << node->key << ", " << *node->value;
            }
            out << "] ";
        }
        out << "\n";
    }
};
