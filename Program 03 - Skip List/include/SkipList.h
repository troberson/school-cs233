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
#include <optional>
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
        std::optional<Key> key;
        std::optional<Value> value;

        std::shared_ptr<Node> next;
        std::shared_ptr<Node> below;

      public:
        explicit Node(std::optional<Key> key = std::nullopt,
                      std::optional<Value> value = std::nullopt,
                      std::shared_ptr<Node> next = nullptr,
                      std::shared_ptr<Node> below = nullptr)
            : key{std::move(key)}, value{std::move(value)},
              next{std::move(next)}, below{std::move(below)}
        {
        }

        Node(Key key, Value value, std::shared_ptr<Node> next = nullptr,
             std::shared_ptr<Node> below = nullptr)
            : next{std::move(next)}, below{std::move(below)}
        {
            this->key = std::make_optional<Key>(key);
            this->value = std::make_optional<Value>(value);
        }


        bool isRoot()
        {
            return !key.has_value();
        }

        std::optional<Key> getKey()
        {
            return key;
        }

        std::optional<Value> getValue()
        {
            return value;
        }

        std::shared_ptr<Node> getNext()
        {
            return next;
        }

        void setNext(std::shared_ptr<Node> node)
        {
            next = node;
        }

        std::shared_ptr<Node> getBelow()
        {
            return below;
        }

        void setBelow(std::shared_ptr<Node> node)
        {
            below = node;
        }

        bool isBottom()
        {
            return this->below == nullptr;
        }
    };

    // the root node of the list
    std::shared_ptr<Node> root = std::make_shared<Node>();

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

        // Decrement list length if node removed
        this->listLength--;
    }

    /*
     * Find the node with the given key.
     *
     * Returns the path taken to find the node.
     *
     * If findInsert is true, return the path to the node prior to where
     * the new node should be inserted.
     *
     * If findInsert is true and key already exists, path is empty.
     * If findInsert is false and key does not exist, path is empty.
     */
    [[nodiscard]] std::vector<std::shared_ptr<Node>>
    find(const Key& findKey, bool findInsert = false) const
    {
        std::vector<std::shared_ptr<Node>> path;

        std::shared_ptr<Node> curNode = this->root;
        while (curNode)
        {
            // Walk forward until we reach a greater key
            while (curNode->getNext() != nullptr &&
                   curNode->getNext()->getKey().value() < findKey)
            {
                curNode = curNode->getNext();
            }

            // Check the current node
            if (!curNode->isRoot())
            {
                // Add to path
                path.push_back(curNode);

                if (findInsert)
                {
                    if (curNode->getKey().value() == findKey)
                    {
                        return {}; // FAIL: Key already present
                    }

                    if (curNode->isBottom())
                    {
                        return path; // SUCCESS: Found a place to insert
                    }
                }
                else
                {
                    if (curNode->getKey().value() == findKey)
                    {
                        return path; // SUCCESS: Found key
                    }

                    if (curNode->isBottom())
                    {
                        return {}; // FAIL: Did not find key
                    }
                }
            }
            curNode = curNode->getBelow();
        }

        return {}; // FAIL: Did not find key
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
            if (!curNode->isRoot())
            {
                keys.emplace_back(curNode->getKey().value());
            }

            curNode = curNode->getNext().get();
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
            auto keys = getLevelKeys(curNode);

            if (!keys.empty())
            {
                out << "L" << level << ": ";
                for (Key k : keys)
                {
                    out << k << " ";
                }
                out << "\n";
            }

            curNode = curNode->getBelow().get();
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
        auto node = std::make_shared<Node>(key, value);

        // If list is empty, set as first node
        if (this->listLength == 0)
        {
            this->root->setNext(node);
            this->listLength++;
            return true;
        }

        // If new node key is less than the first node, put this at the
        // beginning
        if (this->root->getNext() &&
            key < this->root->getNext()->getKey().value())
        {
            node->setNext(this->root->getNext());
            this->root->setNext(node);
            this->listLength++;
            return true;
        }


        // Find where the new node should go
        auto path = find(key, true);

        if (path.empty())
        {
            return false; // FAIL: key already exists
        }

        // std::cout << "Link: " << path.back()->getKey().value() << " to "
        //   << node->getKey().value() << "\n";
        node->setNext(path.back()->getNext());
        path.back()->setNext(node);
        this->listLength++;

        // std::cout << "PATH: ";
        // for (const auto& node : path)
        // {
        //     std::cout << node->getKey().value() << "->";
        // }
        // std::cout << "\n";

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
