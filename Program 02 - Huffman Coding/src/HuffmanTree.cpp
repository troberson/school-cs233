#include "HuffmanTree.h"

#include <algorithm>
#include <array>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

std::string HuffmanTree::getCode(char letter) const
{
    auto result = this->codeLookup.find(letter);
    return ((result != this->codeLookup.end()) ? result->second : "");
}

void HuffmanTree::makeEmpty(BinaryNode*& node)
{
    // need to write code
}

void HuffmanTree::printTree(BinaryNode* node, std::ostream& out) const
{
    // Skip empty nodes
    if (node == nullptr)
    {
        return;
    }

    // Note if the current node is the root of the tree
    if (node == this->root.get())
    {
        out << "Root:\n";
    }

    // Print the current node
    out << node->str() << "\n";

    // Print left and right subtrees
    if (!node->isLeaf())
    {
        out << "Left:\n";
        printTree(node->getLeft(), out);

        out << "Right:\n";
        printTree(node->getRight(), out);
    }
}

void HuffmanTree::printCodes(BinaryNode* node, std::ostream& out) const
{
    // Prepare codes for printing by placing them into a sorted map
    // Sort by the string representation of the binary code
    std::map<std::string, char> codeMap{};

    for (const auto& [c, bitStr] : this->codeLookup)
    {
        codeMap.emplace(bitStr, c);
    }

    // Output:
    //   x = 01011101 (93)
    for (const auto& [bitStr, c] : codeMap)
    {
        // out << std::setw(10 + ASCII_WIDTH) << std::left;
        out << c << " = " << std::left << std::setw(ASCII_WIDTH) << bitStr;

        std::bitset<ASCII_WIDTH> bits{bitStr};
        unsigned long bitLong = bits.to_ullong();
        char bitNum = static_cast<char>(bitLong);

        out << " (" << std::setw(3) << std::right << +bitNum << ")\n";
    }
}


void HuffmanTree::saveTree(BinaryNode* current, std::string code)
{
    // need to write code
}

// writes tree information to file so the tree can be rebuilt when
// unzipping
void HuffmanTree::saveTree(std::ostream& compressedFileStream)
{
    // need to write code
    // calls recursive function
}


void HuffmanTree::rebuildTree(BinaryNode* node, std::string element,
                              std::string codedRoute)
{

    // need to write code
}

void HuffmanTree::rebuildTree(std::ifstream& compressedFile)
{
    // read info from file
    // use info to build tree

    // need to write code
    // calls recursive function
}

std::shared_ptr<HuffmanTree::BinaryNode>
HuffmanTree::buildTree(const std::string& frequencyText)
{
    // Ergonomics
    using node_t = HuffmanTree::BinaryNode;
    using node_ptr_t = std::shared_ptr<node_t>;

    // Build a priority queue of nodes for each unique character in the
    // text, such that the top node is the least frequent (weakly ordered).
    auto cmp = [](auto left, auto right) { return *left > *right; };

    std::priority_queue<node_ptr_t, std::vector<node_ptr_t>, decltype(cmp)>
        nodes(cmp);

    // The DEL character causes problems, skip it
    for (char c = 0; c <= ASCII_MAX && c != ASCII_DEL; c++)
    {
        int f = std::count(frequencyText.begin(), frequencyText.end(), c);

        if (f > 0)
        {
            nodes.emplace(std::make_shared<node_t>(c, f));
        }
    }

    // Unfortunately, pop() is void. We need both top() and pop() together
    auto getNext = [&nodes]() {
        auto n = nodes.top();
        if (n)
        {
            nodes.pop();
        }
        return n;
    };

    // Build a tree from the priority queue
    // Each time, take up to two nodes in the queue for left and right.
    // Then create a parent for those nodes and add the parent node with a
    //   combined weight of its children into the queue.
    // The last remaining node in the queue will be the root.
    while (nodes.size() > 1)
    {
        // Left: We will always have at least one node for the left
        auto leftNode = getNext();
        int freq = leftNode->getFrequency();

        // Right: We may not have a node for the right
        auto rightNode = getNext();
        if (rightNode != nullptr)
        {
            freq += rightNode->getFrequency();
        }

        // Create a parent for these two nodes
        auto newNode = std::make_shared<node_t>(0, freq);
        newNode->setLeft(std::move(leftNode));
        newNode->setRight(std::move(rightNode));
        nodes.push(newNode);
    }

    // Return the root node
    return nodes.top();
}

// Build the lookup table.
//   If a node is on the left, the bit at the depth position is 0
//   If a node is on the right, the bit at the depth position is 1
void HuffmanTree::buildTable(
    BinaryNode* node,
    std::bitset<ASCII_WIDTH> bits = std::bitset<ASCII_WIDTH>{},
    int depth = 0)
{
    // Skip empty nodes
    if (node == nullptr)
    {
        return;
    }

    depth++;

    // Process left subtree
    buildTable(node->getLeft(), bits, depth);

    // Process right subtree
    bits.set(bits.size() - depth);
    buildTable(node->getRight(), bits, depth);
    bits.set(bits.size() - depth, false);

    depth--;

    // Process current node
    if (node->isLeaf())
    {
        this->codeLookup.emplace(node->getElement(),
                                 bits.to_string().substr(0, depth));
    }
}

HuffmanTree::HuffmanTree(std::string frequencyText)
{
    root = buildTree(frequencyText);
    buildTable(root.get());
    // saveTree(root, string());   // build the lookupTable for codes...can
    // write later
}

HuffmanTree::HuffmanTree(std::ifstream& frequencyStream)
{

    std::string frequencyText(
        (std::istreambuf_iterator<char>(frequencyStream)),
        std::istreambuf_iterator<char>());
    frequencyStream.close();
    if (frequencyText.empty())
    {
        root = buildTree(frequencyText);
        // saveTree(root, string());   // build the lookupTable for codes
    }
}

// print out the char and its encoding
void HuffmanTree::printCodes(std::ostream& out) const
{
    printCodes(this->root.get(), out);
}

// prints out the char and frequency
void HuffmanTree::printTree(std::ostream& out) const
{
    printTree(this->root.get(), out);
}

void HuffmanTree::makeEmpty()
{
    // need to write code
    // calls recursive function
}

std::string HuffmanTree::decode(std::vector<char> encodedBytes)
{
    std::string decoded;

    // need to write code

    return decoded;
}

std::vector<char> HuffmanTree::encode(std::string stringToEncode)
{
    stringToEncode.push_back(
        EOFCharacter); // needed when encoding message for file I/O

    std::vector<char> encoded;

    // need to write code

    return encoded;
}

void HuffmanTree::uncompressFile(std::string compressedFileName,
                                 std::string uncompressToFileName)
{
    // need to write code

    // NOTE: when opening the compressedFile, you need to open in
    //  binary mode for reading..hmmm..why is that?
}

void HuffmanTree::compressFile(std::string compressToFileName,
                               std::string uncompressedFileName,
                               bool buildNewTree)
{
    // need to write code

    // NOTE: when opening the compressedFile, you need to open in
    //  binary mode for writing..hmmm..why is that?
}
