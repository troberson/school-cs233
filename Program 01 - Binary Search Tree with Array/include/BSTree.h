///
// Name: Tamara Roberson
// Section: A
// Program Name: Program 1 - Binary Search Tree with Array
//
// Description: A Binary Search Tree which is backed by an array.
//
// The tree holds nodes where the key is any type and the value is a
// pointer.
//
// The tree has functions to find the value associated with the minimum or
// maximum key or any given key. The tree can also be printed as values
// sorted in order of keys.
//
// Lookups are fast, O(log n). However, insertions may be slow if the array
// needs to grow (which requires copying the entire array to a new, larger
// array). Deletions may be moderately slow, as any children of the deleted
// node may need to be shifted up the array.
///

#include "BSTInterface.h"

#include <algorithm>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

template <typename KeyComparable, typename Value>
class BinarySearchTree : BSTInterface<KeyComparable, Value>
{
  public:
    inline static int DEFAULT_SIZE = 25;

  private:
    /*
     * Private Node Class
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
    Pair** root = createTree();

    /*
     * Return a newly created pointer to an array of Pairs of given size
     * (or default) for a new tree.
     */
    static auto createTree(int capacity = DEFAULT_SIZE)
    {
        return new Pair*[capacity]();
    }

    /*
     * Delete the current tree.
     */
    void deleteTree()
    {
        for (size_t i = 1; i < this->size; i++)
        {
            deleteNodeAt(i, /* doShift */ false);
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
     * Throws std::invalid_argument if the index is invalid or if the node
     * is empty
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
     * If doShift is true [default: true], shift the subtrees of the delete
     * node up, so everything remains in order. Use false for a quick
     * delete.
     *
     * Throws std::out_of_range if index is invalid.
     */
    void deleteNodeAt(int index, bool doShift = true)
    {
        assertValidIndex(index);

        if (!hasNodeAt(index))
        {
            return; // RETURN: Nothing to delete
        }

        // Delete the node
        delete this->root[index];
        this->root[index] = nullptr;

        // Update count
        this->count--;

        // If shifting, shift children up
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
        assertValidIndex(index);

        if (hasNodeAt(index))
        {
            return; // RETURN: Don't shift, there's an element here
        }

        auto swapNodes = [&](int newIndex) {
            if (hasNodeAt(newIndex))
            {
                std::swap(this->root[index], this->root[newIndex]);
                shift(newIndex);
                return true; // SUCCESS: Nodes swapped
            }
            return false; // FAIL: No nodes to swap
        };

        // Shift left or right subtree
        int lIndex = getLeft(index);
        int rIndex = getRight(index);
        (hasNodeAt(lIndex) && swapNodes(findMax(lIndex))) ||
            (hasNodeAt(rIndex) && swapNodes(findMin(rIndex)));
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
        deleteNodeAt(index, false);

        // Set the replacement node
        this->root[index] = new Pair(key, value);

        // Update count
        this->count++;
    }

    /*
     * Prints the inorder the tree to the stream out
     */
    void printTree(int index, std::ostream& out) const
    {
        if (!isValidIndex(index) || !hasNodeAt(index))
        {
            return; // FAIL: No such node
        }

        // Print Left -> Current -> Right
        printTree(getLeft(index), out);
        out << *getValueAt(index) << "\n";
        printTree(getRight(index), out);
    }

    /*
     * Grow array to a larger size
     */
    void grow(size_t newSize = 0)
    {
        // Check if we actually need to grow
        if (newSize <= this->size)
        {
            return; // RETURN: No need to grow
        }

        // Create a new array and copy the data from the current array
        // into it
        auto newRoot = createTree(newSize);
        std::copy(this->root, this->root + this->size, newRoot);

        // Update the object properties
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
        // Expand the capacity as needed
        // Note: This copies the array, so could be slow.
        if (index >= this->size)
        {
            grow(index + 1);
        }

        assertValidIndex(index);

        // If current index is empty, put the new node there
        if (!hasNodeAt(index))
        {
            setNode(key, value, index);
            return true; // SUCCESS: Key added
        }

        auto currentKey = getKeyAt(index);

        // Check if key is already in the tree
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

        // Keep walking until there's no more nodes in that direction
        for (int newIndex = index; hasNodeAt(newIndex);
             newIndex = walk(index))
        {
            index = newIndex;
        }

        // Return the last valid index
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
     * Search for the given key starting at the given index.
     * Returns the index of the node or 0 if not found.
     */
    [[nodiscard]] int find(const KeyComparable& key, const int index) const
    {
        if (!hasNodeAt(index))
        {
            return 0; // FAIL: Not found.
        }

        auto currentKey = getKeyAt(index);

        // Check current node
        if (currentKey == key)
        {
            return index; // SUCCESS: Found the key.
        }

        // Search left or right subtrees
        int newIndex =
            (key < currentKey) ? getLeft(index) : getRight(index);

        return find(key, newIndex);
    }


  public:
    /*
     * CONSTRUCTOR
     */
    BinarySearchTree() = default;

    /*
     * DESTRUCTOR
     */
    ~BinarySearchTree() override
    {
        deleteTree();
    }

    /*
     * Finds the node with the smallest element in the tree
     */
    [[nodiscard]] const Value findMin() const override
    {
        int found = findLast(1, getLeft);
        return hasNodeAt(found) ? getValueAt(found) : nullptr;
    }

    /*
     * Finds the node with the largest element in the tree
     */
    [[nodiscard]] const Value findMax() const override
    {
        int found = findLast(1, getRight);
        return hasNodeAt(found) ? getValueAt(found) : nullptr;
    }

    /*
     * Finds the node with that the key
     * updates the founditem refrerence if found
     * returns true if it was found
     * returns false if it was not
     */
    bool find(const KeyComparable& key,
              /* out */ Value& founditem) const override
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
    [[nodiscard]] bool contains(const KeyComparable& key) const override
    {
        return find(key, 1) > 0;
    }

    /*
     * Returns true if tree has no nodes
     */
    [[nodiscard]] bool isEmpty() const override
    {
        return this->count == 0;
    }

    /*
     * Prints the inorder the tree to the stream out
     */
    void printTree(std::ostream& out = std::cout) const override
    {
        printTree(1, out);
    }

    /*
     * Removes all nodes from the tree and replaces it with a default
     * setup.
     */
    void makeEmpty() override
    {
        deleteTree();
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
        int index = find(key, 1);
        if (index < 1)
        {
            return; // Key not found.
        }
        deleteNodeAt(index, true);
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
    void printArray(std::ostream& out = std::cout) const
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
