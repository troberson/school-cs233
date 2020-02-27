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
///

#pragma once

#include <iostream>
#include <memory>
#include <string>

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
    std::unique_ptr<Node> root;

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
     * Prints the list stream out
     */
    void displayList(Node* node, std::ostream& out) const
    {
        // Skip null nodes
        if (!node)
        {
            return;
        }
    }

  public:
    /*
     * Finds the node with that the key
     */
    Value& find(const Key& key) const
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
    bool insert(Value item, Key key)
    {
        return true; // SUCCESS: node added
    }


    bool insert(Key key, Value value)
    {
        // If there is no root node, add this as the root
        if (!root)
        {
            root = std::make_unique<Node>(key, value);
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
