#include "BSTInterface.h"

#include <algorithm>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std;
template <typename KeyComparable, typename Value>
class BinarySearchTree : BSTInterface<KeyComparable, Value>
{
  public:
    inline static size_t DEFAULT_SIZE = 25;

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
    Pair** root;

    /*
     * Return a newly created pointer to an array of Pairs of given size
     * (or default) for a new tree.
     */
    auto createTree(size_t capacity = DEFAULT_SIZE)
    {
        return new Pair*[capacity]();
    }

    /*
     * Delete the current tree.
     * If deep is true, also delete the data held in the values.
     * Otherwise, do a shallow delete and delete only the Pair objects.
     */
    void deleteTree(bool deep = false)
    {
        // std::cout << "Deleting Tree! " << (deep ? "DEEP" : "") << "\n";

        for (size_t i = 1; i < this->size; i++)
        {
            deleteNodeAt(i, deep, false);
        }

        delete[] this->root;
    }

    /*
     * Returns the index of the left child of a given index.
     */
    [[nodiscard]] static int getLeft(int index) noexcept
    {
        return 2 * index;
    }

    /*
     * Returns the index of the right child of a given index.
     */
    [[nodiscard]] static int getRight(int index) noexcept
    {
        return 2 * index + 1;
    }

    /*
     * Returns the index of the parent of an index or 0 if node is root
     * or invalid
     */
    [[nodiscard]] int getParent(int index) const noexcept
    {
        if (index <= 1)
        {
            return 0;
        }

        return index / 2;
    }

    /*
     * Returns true if the given index is in the range of [1, size),
     * false otherwise. Note: This structure is 1-indexed, so 0 is not
     * a valid index.
     */

    [[nodiscard]] bool isValidIndex(int idx) const noexcept
    {
        return (idx >= 1 && idx < this->size);
    }

    /*
     * Asserts that the given index is valid.
     * If it is invalid, a std::out_of_range exception is thrown.
     */
    void assertValidIndex(int idx) const
    {
        if (!isValidIndex(idx))
        {
            // FAIL: Invalid index
            auto msg =
                std::string("Invalid index: ") + std::to_string(idx);
            throw std::out_of_range(msg);
        }
    }

    /*
     * Returns true if there is a non-empty node at the given index,
     * false otherwise.
     */
    [[nodiscard]] bool hasNodeAt(int index) const noexcept
    {
        return isValidIndex(index) && this->root[index];
    }

    /*
     * Asserts that there must be a non-empty node at the given index.
     * If the index is invalid or the node is empty, a
     * std::invalid_argument is thrown.
     */
    void assertHasNodeAt(int index) const
    {
        if (!hasNodeAt(index))
        {
            // FAIL: Empty node
            auto msg = std::string("Node is empty, Index: ") +
                       std::to_string(index);
            throw std::invalid_argument(msg);
        }
    }

    /*
     * Returns a pointer to the Pair at the given index.
     * Throws std::out_of_range if index is invalid.
     * Throws std::invalid_argument if Node at the given index is
     * empty.
     */
    [[nodiscard]] Pair* getNodeAt(int index) const
    {
        assertHasNodeAt(index);
        return this->root[index];
    }

    /*
     * Returns the key at the given index.
     * Throws std::out_of_range if index is invalid.
     * Throws std::invalid_argument if Node at the given index is
     * empty.
     */
    [[nodiscard]] KeyComparable getKeyAt(int index) const
    {
        return getNodeAt(index)->key;
    }

    /*
     * Returns the value at the given index.
     * Note: The value is a pointer to an underlying value.
     * Throws std::out_of_range if index is invalid.
     * Throws std::invalid_argument if Node at the given index is
     * empty.
     */
    [[nodiscard]] Value getValueAt(int index) const
    {
        return getNodeAt(index)->value;
    }

    /*
     * Delete node at a given index.
     *
     * If deep is true [default: false], also delete the data held in the
     * values. Otherwise, do a shallow delete and delete only the Pair
     * object.
     *
     * If doShift is true [default: true], shift the subtrees of the delete
     * node up, so everything remains in order. Use false for a quick
     * delete.
     *
     * Throws std::out_of_range if index is invalid.
     */
    void deleteNodeAt(int index, bool deep = false, bool doShift = true)
    {
        assertValidIndex(index);

        if (!hasNodeAt(index))
        {
            return; // RETURN: Nothing to delete
        }

        // std::cout << "Deleting Node at Index " << index << " ["
        //           << getKeyAt(index) << ", " << getValueAt(index) << "]
        //           "
        //           << (deep ? "DEEP" : "") << "\n";
        if (deep)
        {
            Value val = getValueAt(index);
            delete val;
        }

        delete this->root[index];
        this->root[index] = nullptr;

        this->count--;

        if (doShift)
        {
            shift(index);
        }
    }

    /*
     * Shift remaining nodes up after deleting.
     */
    void shift(int index)
    {
        // std::cout << "Shift Index " << index << "\n";
        assertValidIndex(index);

        if (hasNodeAt(index))
        {
            // RETURN: No need to shift, there is an element here
            // already.
            return;
        }

        // Shift left subtree
        int leftIndex = getLeft(index);
        if (hasNodeAt(leftIndex))
        {
            int maxLeft = findMax(leftIndex);
            if (hasNodeAt(maxLeft))
            {
                std::swap(this->root[index], this->root[maxLeft]);
                shift(maxLeft);
                // return;
            }
        }

        // Shift right subtree
        int rightIndex = getRight(index);
        if (hasNodeAt(rightIndex))
        {
            int minRight = findMin(rightIndex);
            if (hasNodeAt(minRight))
            {
                std::swap(this->root[index], this->root[minRight]);
                shift(minRight);
                // return;
            }
        }
    }

    /*
     * Assigns a (key, value) Pair to the node at the given index.
     * Will delete any existing data.
     * Throws std::out_of_range if index is invalid.
     */
    void setNode(KeyComparable key, Value value, int index)
    {
        assertValidIndex(index);

        // Delete any existing data
        deleteNodeAt(index, false, false);

        // Set the replacement node
        this->root[index] = new Pair(key, value);
        this->count++;
    }

    /*
     * Prints the inorder the tree to the stream out
     *
     */
    void printTree(int index, std::ostream& out) const
    {
        if (!isValidIndex(index))
        {
            // std::cout << "DEBUG: Invalid Index " << index << " Size
            // is "
            //           << this->size << "\n";
            return; // FAIL: no such node
        }

        if (!hasNodeAt(index))
        {
            // std::cout << "DEBUG: Empty Index " << index << "\n";
            return; // FAIL: this node is empty
        }

        // out << "DEBUG: Print Left (" << index << ")\n";
        printTree(getLeft(index), out);
        // out << "DEBUG: Current (" << index << "): " ;
        out << *getValueAt(index) << "\n";
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

        // create a new array and copy the data from the current array
        // into it
        auto newRoot = createTree(newSize);
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

        // Expand the capacity as needed
        // Note, this requires copying the whole array, so could be
        // slow.
        if (index >= this->size)
        {
            // cout << "Current array size is " << this->size
            //      << ", growing to " << index << "\n";
            grow(index + 1);
        }

        assertValidIndex(index);

        // If current index is empty, put the new node there
        if (!hasNodeAt(index))
        {
            // cout << "Current Node is empty, adding key " << key <<
            // "\n";
            setNode(key, value, index);
            return true; // SUCCESS: Key added
        }

        auto currentKey = getKeyAt(index);
        // cout << "Current Node has Key " << curNode->key << "\n";

        // Check if the key is the same as the current key (already
        // exists)
        if (key == currentKey)
        {
            return false; // FAIL: Key already exists
        }

        // Use left branch for smaller keys
        // Use right branch for larger keys
        int newIndex =
            (key < currentKey) ? getLeft(index) : getRight(index);

        return insert(key, value, newIndex);
    }

    /*
     * Returns the last valid index after recursive calls of
     * WalkFunction
     */
    template <typename WalkFunction>
    [[nodiscard]] int findLast(int index, WalkFunction walk) const
    {
        assertHasNodeAt(index);

        for (int newIndex = index; hasNodeAt(newIndex);
             newIndex = walk(index))
        {
            index = newIndex;
        }

        return index;
    }

    /*
     * Finds the index of the node with the smallest key below the
     * given index
     */
    [[nodiscard]] int findMin(int index) const
    {
        return findLast(index, getLeft);
    }

    /*
     * Finds the index of the node with the largest key below the given
     * index
     */
    [[nodiscard]] int findMax(int index) const
    {
        return findLast(index, getRight);
    }

    /*
     * Returns the value at the last valid index returned by
     * WalkFunction
     */
    template <typename WalkFunction>
    [[nodiscard]] Value findLastValue(int index, WalkFunction walk) const
    {
        int found = findLast(index, walk);
        return hasNodeAt(found) ? getValueAt(found) : nullptr;
    }

    /*
     * Finds the value of the node with the smallest key below the
     * given index
     */
    [[nodiscard]] Value findMinValue(int index) const
    {
        return findLastValue(index, getLeft);
    }

    /*
     * Finds the node with the largest key below the given index
     */
    [[nodiscard]] Value findMaxValue(int index) const
    {
        return findLastValue(index, getRight);
    }

    /*
     * Search for the given key starting at the given index.
     * Returns the index of the node or 0 if not found.
     */
    [[nodiscard]] int find(const KeyComparable& key, const int index) const
    {
        // std::cout << "Searching for key " << key << " starting at
        // index
        // "
        //           << index << "\n";

        if (!hasNodeAt(index))
        {
            // std::cout << "Index " << index << " is empty.\n";
            return 0;
        }

        auto currentKey = getKeyAt(index);

        if (currentKey == key)
        {
            // std::cout << "SUCCESS: Found key at index " << index <<
            // "\n";
            return index; // SUCCESS: Found the key.
        }

        int newIndex =
            (key < currentKey) ? getLeft(index) : getRight(index);

        if (!hasNodeAt(index))
        {
            return 0; // FAIL: Not found.
        }

        // Keep searching
        return find(key, newIndex);
    }


  public:
    /*
     * CONSTRUCTOR
     */
    BinarySearchTree()
    {
        this->root = createTree();
    }

    /*
     * DESTRUCTOR
     */
    ~BinarySearchTree()
    {
        // std::cout << "DESTRUCTOR.\n";
        deleteTree(true);
    }

    /*
     * Finds the node with the smallest element in the tree
     */
    [[nodiscard]] const Value findMin() const override
    {
        return findMinValue(1);
    }

    /*
     * Finds the node with the largest element in the tree
     */
    [[nodiscard]] const Value findMax() const override
    {
        return findMaxValue(1);
    }

    /*
     * Finds the node with that the key
     * updates the founditem refrerence if found
     * returns true if it was found
     * returns false if it was not
     */
    bool find(const KeyComparable& key, /* out */ Value& founditem) const
    {
        int index = find(key, 1);
        if (index < 1)
        {
            return false; // FAIL: key not found
        }

        // extract value into the founditem outparam.
        founditem = getValueAt(index);
        return true; // SUCCESS
    }

    /*
     * Returns true if the item is found in the tree
     */
    bool contains(const KeyComparable& key) const
    {
        return find(key, 1) > 0;
    }

    /*
     * Returns true if tree has no nodes
     */
    bool isEmpty() const
    {
        return this->count == 0;
    }

    /*
     * Prints the inorder the tree to the stream out
     */
    void printTree(std::ostream& out = cout) const
    {
        printTree(1, out);

        // std::cout << "Counting nodes.\n";
        int num{0};
        for (int i = 1; i < this->size; i++)
        {
            // std::cout << "Node Index " << i << ": ";
            if (hasNodeAt(i))
            {
                // std::cout << "X";
                num++;
            }
            // std::cout << "\n";
        }

        //     std::cout << "Node Count Should Be: " << num << " and is "
        //               << this->count << "\n";
    }

    /*
     * Removes all nodes from the tree and replaces it with a default
     * setup.
     */
    void makeEmpty() override
    {
        deleteTree(true);
        this->root = createTree();
        this->size = DEFAULT_SIZE;
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
    void remove(const KeyComparable& key) override
    {
        // std::cout << "Remove Key: " << key << "\n";
        int index = find(key, 1);
        if (index < 1)
        {
            // std::cout << "KEY NOT FOUND!\n";
            return; // Key not found.
        }
        deleteNodeAt(index, true, true);
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
            if (hasNodeAt(i))
            {
                auto node = getNodeAt(i);
                out << node->key << ", " << *node->value;
            }
            out << "] ";
        }
        out << "\n";
    }
};
