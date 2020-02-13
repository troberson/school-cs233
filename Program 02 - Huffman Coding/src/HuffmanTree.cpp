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
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

std::string readStream(std::ifstream& inputStream, uintmax_t size = 0);


std::string readStream(std::ifstream& inputStream,
                       uintmax_t size /* = 0 */)
{
    std::stringstream buffer;

    // preallocate if size is known
    if (size > 0)
    {
        buffer = std::stringstream(std::string(size, ' '));
    }

    buffer << inputStream.rdbuf();
    return buffer.str();
}


std::string HuffmanTree::getCode(char letter) const
{
    auto result = this->codeLookup.find(letter);
    return ((result != this->codeLookup.end()) ? result->second : "");
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

// writes tree information to file so the tree can be rebuilt when
// unzipping
std::string HuffmanTree::saveTable()
{
    std::stringstream codebook;
    for (char c = 0; c <= CHAR_MAX && c != ASCII_DEL; c++)
    {
        int len = 0;
        auto entry = this->codeLookup.find(c);
        if (entry != this->codeLookup.end())
        {
            len = entry->second.length();
        }
        codebook << std::to_string(len) << " ";
    }
    return codebook.str();
}

std::unordered_map<char, std::string>
HuffmanTree::rebuildTable(const std::string& codebookStr)
{
    // decode the codebook string into a list of numbers
    std::stringstream codeStream(codebookStr);
    int num;
    std::vector<int> codeLengths;
    codeLengths.reserve(CHAR_MAX);
    while (codeStream >> num)
    {
        codeLengths.push_back(num);
    }

    std::vector<std::pair<char, int>> bitLengths;

    for (char c = 0; c <= CHAR_MAX && c != ASCII_DEL; c++)
    {
        if (codeLengths[c] == 0)
        {
            continue;
        }

        bitLengths.emplace_back(std::make_pair(c, codeLengths[c]));
    }

    std::stable_sort(bitLengths.begin(), bitLengths.end(),
                     [](const std::pair<char, int>& lhs,
                        const std::pair<char, int>& rhs) {
                         return lhs.second < rhs.second;
                     });

    return makeCodebook(bitLengths);
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
    for (char c = 0; c <= CHAR_MAX && c != ASCII_DEL; c++)
    {
        int f = std::count(frequencyText.begin(), frequencyText.end(), c);


        if (f > 0)
        {
            nodes.emplace(std::make_shared<node_t>(c, f));
        }
    }

    // Add the EOF Character (NULL) to the string, so when decoded, we will
    // know when the text ends.
    nodes.emplace(std::make_shared<node_t>(this->EOFCharacter, 1));

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
void HuffmanTree::buildTable(BinaryNode* node,
                             std::bitset<CODE_WIDTH> bits, int depth)
{
    // Skip empty nodes
    if (node == nullptr)
    {
        return;
    }

    // Process left and right subtrees if we're not at the last row
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
        this->codeLookup.emplace(node->getElement(),
                                 bits.to_string().substr(0, depth));
    }
}


// Make Canonical
// Convert a table from a general Huffman code into a Canonical Huffman
// Code
std::unordered_map<char, std::string>
HuffmanTree::makeCanonical(std::unordered_map<char, std::string> oldTable)
{
    auto sorter = [](const std::pair<char, std::string>& lhs,
                     const std::pair<char, std::string>& rhs) {
        return lhs.second.size() == rhs.second.size()
                   ? lhs.first < rhs.first
                   : lhs.second.size() < rhs.second.size();
    };

    std::set<std::pair<char, std::string>, decltype(sorter)> sortedPairs(
        oldTable.begin(), oldTable.end(), sorter);

    std::vector<std::pair<char, int>> bitLengths;
    bitLengths.reserve(sortedPairs.size());
    for (const auto& [c, bitStr] : sortedPairs)
    {
        bitLengths.emplace_back(std::make_pair(c, bitStr.length()));
    }

    return makeCodebook(bitLengths);
}


std::unordered_map<char, std::string> HuffmanTree::makeCodebook(
    const std::vector<std::pair<char, int>>& bitLengths)
{
    std::unordered_map<char, std::string> newTable;

    unsigned int prevLength = 0;
    unsigned long count = -1;

    for (const auto& [c, len] : bitLengths)
    {
        count++;

        if (len > prevLength)
        {
            count <<= (len - prevLength);
            prevLength = len;
        }

        std::bitset<CODE_WIDTH> newBits(count);
        newBits <<= CODE_WIDTH - len;
        std::string newBitStr = newBits.to_string();
        newBitStr = newBitStr.substr(0, len);
        newTable.emplace(c, newBitStr);
    }

    return newTable;
}

void HuffmanTree::build(const std::string& frequencyText)
{
    this->root = buildTree(frequencyText);
    buildTable(this->root.get());
    this->codeLookup = makeCanonical(this->codeLookup);
    this->codebook = saveTable();
}

void HuffmanTree::build(std::ifstream& frequencyStream)
{
    build(readStream(frequencyStream));
}


HuffmanTree::HuffmanTree(const std::string& frequencyText)
{
    build(frequencyText);
}

HuffmanTree::HuffmanTree(std::ifstream& frequencyStream)
{
    build(frequencyStream);
}

void HuffmanTree::printBinary(const std::vector<char>& bytes,
                              std::ostream& out) const
{
    for (const unsigned long long bitNum : bytes)
    {
        std::bitset<CHAR_WIDTH> bits{bitNum};

        out << bits << " (" << bits.to_ulong() << ") - ";
    }
    out << "END\n";
}

void HuffmanTree::printCodes(std::ostream& out) const
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



void HuffmanTree::printTree(std::ostream& out) const
{
    printTree(this->root.get(), out);
}

void HuffmanTree::makeEmpty()
{
    // Since nodes are linked by shared pointers, everything should clean
    // itself up if we delete the root.
    this->root.reset();
}

auto HuffmanTree::makeDecodeTable(
    const std::unordered_map<char, std::string>& codeLookup)
{
    std::map<int, std::map<std::string, char>> decodeTable;
    for (const auto& [c, bitStr] : codeLookup)
    {
        int len = bitStr.length();

        if (decodeTable.find(len) == decodeTable.end())
        {
            std::map<std::string, char> codes;
            codes.emplace(bitStr, c);
            decodeTable.emplace(len, codes);
        }
        else
        {
            decodeTable.at(len).emplace(bitStr, c);
        }
    }

    return decodeTable;
}

std::string HuffmanTree::decode(const std::vector<char>& encodedBytes)
{
    std::string decoded;

    if (this->codeLookup.empty())
    {
        this->codeLookup = rebuildTable(this->codebook);
    }

    if (this->decodeTable.empty())
    {
        this->decodeTable = makeDecodeTable(this->codeLookup);
    }

    std::string searchBits;
    for (const unsigned long long bitNum : encodedBytes)
    {
        std::bitset<CHAR_WIDTH> bits{bitNum};

        for (int i = CHAR_WIDTH - 1; i >= 0; i--)
        {
            searchBits += (bits.test(i) ? "1" : "0");

            int len = searchBits.length();
            if (decodeTable.find(len) != decodeTable.end() &&
                decodeTable.at(len).find(searchBits) !=
                    decodeTable.at(len).end())
            {
                char c = decodeTable.at(len).at(searchBits);

                // if we hit EOF, stop where we are and return
                if (c == this->EOFCharacter)
                {
                    return decoded;
                }

                decoded += c;
                searchBits = searchBits.substr(len);
            }
        }
    }

    return decoded; // hopefully we hit the EOF character before this
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

    while (encodedCharStr.length() > CHAR_WIDTH)
    {
        auto newCharStr = encodedCharStr.substr(0, CHAR_WIDTH);
        encoded.emplace_back(getBitNumFromString(newCharStr));
        encodedCharStr.erase(0, CHAR_WIDTH);
    }

    std::bitset<CHAR_WIDTH> newCharBits{encodedCharStr};
    newCharBits <<= CHAR_WIDTH - encodedCharStr.length();
    encoded.push_back(getBitNum(newCharBits));

    return encoded;
}


void HuffmanTree::uncompressFile(std::string compressedFileName,
                                 std::string uncompressToFileName)
{
    std::ifstream inputStream{compressedFileName, std::ios::binary};
    std::ofstream outputStream{uncompressToFileName, std::ios::binary};

    std::string codebook;
    getline(inputStream, codebook, this->EOFCharacter);

    this->codeLookup = rebuildTable(codebook);
    std::stringstream encodedDataStream;
    encodedDataStream << inputStream.rdbuf();

    inputStream.close();

    std::string encodedData = encodedDataStream.str();

    std::vector<char> data(encodedData.begin(), encodedData.end());

    outputStream << decode(data);

    outputStream.close();
}

void HuffmanTree::compressFile(std::string compressToFileName,
                               std::string uncompressedFileName,
                               bool buildNewTree)
{
    std::ifstream inputStream(uncompressedFileName, std::ios::binary);
    std::string text = readStream(inputStream);

    if (buildNewTree)
    {
        build(text);
    }

    std::ofstream outputStream{compressToFileName, std::ios::binary};
    outputStream << this->codebook << this->EOFCharacter;

    std::vector<char> codeList = encode(text);
    std::string encodedText{codeList.begin(), codeList.end()};
    outputStream << encodedText;

    outputStream.close();
}
