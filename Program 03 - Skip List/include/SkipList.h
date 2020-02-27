///
// Name: Tamara Roberson
// Section: A
// Program Name: Program 03 - SkipList
//
// Description: An object-oriented implementation of a SkipList, which is a
// variation of a singly-linked list providing random "express lanes" to
// reduce average lookup times. This implementation includes functions for
// inserting, finding, and removing nodes. The nodes are referenced by a
// key, which can be any comparable type.
//
// Like all linked lists, skip lists have poor cache hit performance. This
// implementation is traditional, with downward links but an alternative is
// described here: http://ticki.github.io/blog/skip-lists-done-right/
///

#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <typename Key, typename Value> class SkipList
{
  private:
    /*
     * Private Node Class
     */
    class Node
    {
      private:
        Key key;
        Value value;

        Node* next;
        Node* below;

      public:
        Node(Key& key, Value& value, Node* next = nullptr,
             Node* below = nullptr)
            : key{key}, value{value}, next{next}, below{below}
        {
        }

        Key getKey()
        {
            return key;
        }

        Value getValue()
        {
            return value;
        }

        Node* getNext()
        {
            return next;
        }

        Node* getBelow()
        {
            return below;
        }

        bool isBottom()
        {
            return this->below == nullptr;
        }
    };

    // the root node of the list
    std::shared_ptr<Node> root;

    // the number of nodes in the bottom row
    int listLength = 0;

    // height of the tallest node
    int listHeight = 0;


    /*
     * Update height to reflect added elements.
     * Grows root's tower to the new height.
     */
    void updateHeight()
    {
        // By repeated "coin flips", the maximum height of the skip list is
        // ceil(log2(n)), where n is the number of nodes in the bottom
        // level. So bypass repeated coin flips and just set the height.
        int newHeight = static_cast<int>(std::ceil(std::log2(listLength)));

        if (newHeight > this->listHeight)
        {
            this->root = growTower(newHeight, this->root).at(0);
            this->listHeight = newHeight;
        }
    }


    /*
     * Return the height of the tower, the number of nodes between the
     * given node and the bottom level.
     */
    int getTowerHeight(Node* startNode)
    {
        int count = 0;
        Node* curNode = startNode;
        while (curNode)
        {
            count++;
            curNode = curNode->getBelow();
        }
        return count;
    }


    /*
     * Grow a tower to add height.
     * Given node should be the top of an existing tower.
     * Returns a list of the nodes added, such that the first element is
     * the top node.
     */
    std::vector<std::shared_ptr<Node>> growTower(int newHeight,
                                                 Node* startNode)
    {
        std::vector<std::shared_ptr<Node>> tower;

        int curHeight = getTowerHeight(startNode);
        Node* curNode = startNode;
        Key key = startNode->getKey();
        Value value = startNode->getValue();

        while (newHeight > curHeight)
        {
            auto newNode =
                std::make_shared<Node>(key, value, nullptr, curNode);

            tower.push_back(newNode);
            curNode = newNode;
        }

        return tower;
    }

    /*
     * remove a node from the list
     */
    void remove(const Key& key, Node* searchNode)
    {
        // Check if the given node is null
        if (!searchNode)
        {
            return; // FAIL: node does not exist
        }

        // decrement list length if node removed
        this->listLength--;
    }

    /*
     * Finds the node with that satisfies equality for the element
     */
    Node* find(const Key& key, Node* searchNode) const
    {
        // Check if the given node is null
        if (!searchNode)
        {
            return nullptr; // FAIL: node does not exist
        }

        // Check the current node
        if (key == searchNode->key)
        {
            return searchNode; // SUCCESS: found the desired node
        }

        return nullptr;
    }


    /*
     * Returns a list of the keys in a level
     */
    std::vector<Key> getLevelKeys(Node* node) const
    {
        std::vector<Key> keys;
        Node* curNode = node;
        while (curNode)
        {
            keys.emplace_back(curNode->getKey());
            curNode = curNode->getNext();
        }
        return keys;
    }

    /*
     * Prints the list stream out
     */
    void displayList(Node* node, std::ostream& out) const
    {
        // Skip null nodes
        if (!node)
        {
            return;
        }

        Node* curNode = node;
        for (int level = this->listHeight; level >= 0; level--)
        {
            out << "L" << level << ": ";
            for (Key k : getLevelKeys(curNode))
            {
                out << k << " ";
            }
            out << "\n";
            curNode = curNode->getBelow();
        }
    }

  public:
    /*
     * Returns the length of the list
     */
    [[nodiscard]] int getLength() const
    {
        return this->listLength;
    }

    /*
     * Finds the node with that the key
     */
    [[nodiscard]] Value& find(const Key& key) const
    {
        return find(key, this->root)->value;
    }

    /*
     * Prints the list to the stream out
     */
    void displayList(std::ostream& out = std::cout) const
    {
        displayList(this->root.get(), out);
    }

    /*
     * Inserts a node into the list
     * returns true if item inserted
     * returns false if item not inserted (Key already in list)
     */
    bool insert(Key key, Value value)
    {
        // If there is no root node, add this as the root
        if (!this->root)
        {
            this->root = std::make_shared<Node>(key, value);
            this->listLength++;
            return true;
        }

        return true;
    }

    /*
     * Removes the nodes if it contains the given item
     */
    void remove(const Key& key)
    {
        remove(key, root.get());
    }
};
