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

    // Is actually finding largest string but that should be the longest
    int maxLength =
        std::max_element(this->codeLookup.begin(), this->codeLookup.end())
            ->second.length();

    // Output:
    //   x = 01011101 (93)
    for (const auto& [bitStr, c] : codeMap)
    {
        out << c << " = " << std::left << std::setw(maxLength) << bitStr;

        std::bitset<CODE_WIDTH> bits{bitStr};
        out << " (" << std::setw(3) << std::right << bits.to_ulong()
            << ")\n";
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
HuffmanTree::buildTree(std::string& frequencyText)
{
    // Ergonomics
    using node_t = HuffmanTree::BinaryNode;
    using node_ptr_t = std::shared_ptr<node_t>;

    // Add the EOF Character (NULL) to the string, so when decoded, we will
    // know when the text ends.
    frequencyText.push_back(this->EOFCharacter);

    // Build a priority queue of nodes for each unique character in the
    // text, such that the top node is the least frequent (weakly ordered).
    auto cmp = [](auto left, auto right) { return *left > *right; };

    std::priority_queue<node_ptr_t, std::vector<node_ptr_t>, decltype(cmp)>
        nodes(cmp);

    // The DEL character causes problems, skip it
    for (char c = 0; c <= CHAR_MAX && c != ASCII_DEL; c++)
    {
        int f = std::count(frequencyText.begin(), frequencyText.end(), c);

        // std::cout << "C: '" << c << "' F:  " << f << "\n";

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

    // Build the lookup table
    buildTable(nodes.top().get());

    // Return the root node
    return nodes.top();
}

// Build the lookup table.
//   If a node is on the left, the bit at the depth position is 0
//   If a node is on the right, the bit at the depth position is 1
void HuffmanTree::buildTable(BinaryNode* node,
                             std::bitset<CODE_WIDTH> bits, int depth)
{
    std::cout << "Depth: " << depth << " ";
    // Skip empty nodes
    if (node == nullptr)
    {
        std::cout << "SKIP\n";
        return;
    }
    std::cout << "\n";


    if (depth < CODE_WIDTH)
    {
        depth++;
        // Process left subtree
        buildTable(node->getLeft(), bits, depth);

        // Process right subtree
        bits.set(bits.size() - depth);
        buildTable(node->getRight(), bits, depth);
        bits.set(bits.size() - depth, false);
        depth--;
    }


    // Process current node
    if (node->isLeaf())
    {
        std::cout << "Char: " << node->getElement() << " Bits: '" << bits
                  << "'\n";
        this->codeLookup.emplace(node->getElement(),
                                 bits.to_string().substr(0, depth));
    }
}

HuffmanTree::HuffmanTree(std::string frequencyText)
{
    root = buildTree(frequencyText);
}

HuffmanTree::HuffmanTree(std::ifstream& frequencyStream)
{

    std::string frequencyText(
        (std::istreambuf_iterator<char>(frequencyStream)),
        std::istreambuf_iterator<char>());
    frequencyStream.close();
    if (!frequencyText.empty())
    {
        std::cout << frequencyText;
        root = buildTree(frequencyText);
    }
}
void HuffmanTree::printBinary(std::vector<char> bytes,
                              std::ostream& out) const
{
    for (const unsigned long long bitNum : bytes)
    {
        std::bitset<CHAR_WIDTH> bits{bitNum};

        out << bits << " (" << bits.to_ulong() << ") - ";
    }
    out << "END\n";
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

    auto curNode = this->root.get();

    for (const unsigned long long bitNum : encodedBytes)
    {
        std::bitset<CHAR_WIDTH> bits{bitNum};

        for (int i = CHAR_WIDTH - 1; i >= 0; i--)
        {
            curNode =
                (bits.test(i)) ? curNode->getRight() : curNode->getLeft();

            if (curNode->isLeaf())
            {
                // Stop if we reach the EOF Character
                if (curNode->getElement() == this->EOFCharacter)
                {
                    break;
                }

                // Add the character and start over at root
                decoded.push_back(curNode->getElement());
                curNode = this->root.get();
            }
        }
    }

    return decoded;
}

std::vector<char> HuffmanTree::encode(std::string stringToEncode)
{
    // needed when encoding message for file I/O
    stringToEncode.push_back(EOFCharacter);

    auto getBitNum = [](const std::bitset<CHAR_WIDTH>& bits) {
        return static_cast<char>(bits.to_ulong());
    };

    auto getBitNumFromString = [getBitNum](const std::string& bitStr) {
        std::bitset<CHAR_WIDTH> bits{bitStr};
        return getBitNum(bits);
    };


    std::vector<char> encoded;

    std::string encodedCharStr;
    for (const char c : stringToEncode)
    {
        // May throw std::out_of_range if character is not in tree
        std::string bitStr;
        try
        {
            bitStr = this->codeLookup.at(c);
        }
        catch (...)
        {
            std::cerr << "ERROR: Character '" << c
                      << "' cannot be encoded.\n";
            throw;
        }

        encodedCharStr += bitStr;

        if (encodedCharStr.length() > CHAR_WIDTH)
        {
            auto newCharStr = encodedCharStr.substr(0, CHAR_WIDTH);
            encoded.emplace_back(getBitNumFromString(newCharStr));
            encodedCharStr.erase(0, CHAR_WIDTH);
        }
    }

    std::bitset<CHAR_WIDTH> newCharBits{encodedCharStr};
    newCharBits <<= CHAR_WIDTH - encodedCharStr.length();
    encoded.push_back(getBitNum(newCharBits));

    printBinary(encoded);

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
