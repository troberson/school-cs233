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

#include <iostream>
#include <memory>
#include <optional>
#include <random>
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

    // random number generator
    std::random_device rndDev;
    std::mt19937 rndGen;
    std::bernoulli_distribution rndDist;

    /*
     * Increase list height by one.
     * Grows root's tower to the new height.
     */
    void increaseHeight()
    {
        auto newRoot = std::make_shared<Node>();
        newRoot->setBelow(this->root);
        this->root = newRoot;
        this->listHeight++;
    }

    /*
     * Returns a list of nodes representing a tower
     */
    std::vector<std::shared_ptr<Node>>
    getTower(std::shared_ptr<Node> startNode)
    {
        std::vector<std::shared_ptr<Node>> tower;
        auto curNode = startNode;
        tower.push_back(curNode);
        while (!curNode->isBottom())
        {
            curNode = curNode->getBelow();
            tower.push_back(curNode);
        }
        return tower;
    }


    /*
     * Return the bottom node of the current tower
     */
    std::shared_ptr<Node> findBottom(std::shared_ptr<Node> startNode)
    {
        return getTower(startNode).back();
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
                   curNode->getNext()->getKey().value() <= findKey)
            {
                curNode = curNode->getNext();
                if (!findInsert)
                {
                    path.push_back(curNode);
                }
            }

            // Check the current node
            if (!curNode->isRoot())
            {
                if (findInsert)
                {
                    if (curNode->getKey().value() == findKey)
                    {
                        return {}; // FAIL: Key already present
                    }

                    if (curNode->isBottom())
                    {
                        path.push_back(curNode);
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
            // Add to path for findInsert
            if (findInsert)
            {
                path.push_back(curNode);
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


    /*
     * Insert a new node with the given find path.
     * Returns true if inserted, false otherwise.
     */
    void insert(Key key, Value value,
                std::vector<std::shared_ptr<Node>>& path)
    {
        this->listLength++;

        auto node = std::make_shared<Node>(key, value);

        // First element added
        if (this->listLength == 1)
        {
            this->root->setNext(node);
            return;
        }

        // If there is no other path, set the path to root tower
        if (path.empty())
        {
            path = getTower(this->root);
        }

        // Link to the previous node in the path
        std::shared_ptr<Node> prev = path.back();
        path.pop_back();
        node->setNext(prev->getNext());
        prev->setNext(node);

        // Randomly increase the height of the tree
        int height = 0;
        while (this->rndDist(this->rndGen))
        {
            // If we're taller than the root tower, grow the root
            height++;
            if (height > this->listHeight)
            {
                increaseHeight();
            }

            // If we have no other path, link to the top of the root tower
            if (path.empty())
            {
                path.push_back(this->root);
            }

            // Create and link a new level to the path
            std::shared_ptr<Node> prev = path.back();
            path.pop_back();

            auto newNode =
                std::make_shared<Node>(key, value, prev->getNext(), node);

            prev->setNext(newNode);
            node = newNode;
        }
    }

    /* ***
     * *** PUBLIC
     * ***/

  public:
    /*
     * Constructor
     */
    explicit SkipList()
    {
        rndGen = std::mt19937{rndDev()};
        rndDist = std::bernoulli_distribution(0.5);
    }

    /*
     * Returns the length of the list
     */
    [[nodiscard]] int getLength() const
    {
        return this->listLength;
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
        std::vector<std::shared_ptr<Node>> path;
        auto node = std::make_shared<Node>(key, value);

        // Check if should go at the beginning
        if (this->listLength == 0 ||
            key < findBottom(this->root)->getNext()->getKey().value())
        {
            insert(key, value, path);
            return true;
        }

        // Find where the new node should go
        path = find(key, true);

        if (path.empty())
        {
            return false; // FAIL: key already exists
        }

        // Insert node
        insert(key, value, path);
        return true;
    }

    /*
     * Removes the nodes if it contains the given item
     */
    void remove(const Key& key)
    {
        // For every level, look for the key and remove it
        for (const auto& level : getTower(this->root))
        {
            std::shared_ptr<Node> prev = level;
            std::shared_ptr<Node> curNode = level->getNext();

            // Walk through the level until we reach a key equal or larger
            // than the one we are looking for
            while (curNode && curNode->getKey().value() <= key)
            {
                // If we found the key, unlink it
                if (curNode->getKey().value() == key)
                {
                    prev->setNext(curNode->getNext());

                    // The list length only counts bottom level nodes
                    if (curNode->isBottom())
                    {
                        this->listLength--;
                    }
                    break;
                }

                // Keep walking
                prev = curNode;
                curNode = curNode->getNext();
            }
        }
    }
};
