#include "HuffmanTree.h"
#include <algorithm>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

inline bool HuffmanTree::getBit(unsigned char byte, int position) const
{
    return (byte & BITMASK[position]);
}

// Usage
// mybyte = setBit(mybyte,4);
// This sets the bit in position 4
inline unsigned char HuffmanTree::setBit(unsigned char byte,
                                         int position) const
{
    return byte | BITMASK[position];
}

void HuffmanTree::printBits(char binary, std::ostream& out) const
{
    for (size_t i = 0; i < sizeof(char) * 8; i++)
    {
        if (getBit(binary, i))
        {
            out << 1;
        }
        else
        {
            out << 0;
        }
    }
}

void HuffmanTree::printBinary(std::vector<char> bytes,
                              std::ostream& out) const
{
    for (char byte : bytes)
    {
        printBits(byte, out);
        out << "-";
    }
}

std::string HuffmanTree::getCode(char letter) const
{
    std::string code = "";

    // need to write code

    return code;
}

void HuffmanTree::makeEmpty(BinaryNode*& node)
{
    // need to write code
}

void HuffmanTree::printTree(BinaryNode* node, std::ostream& out) const
{
    // need to write code
}

void HuffmanTree::printCodes(BinaryNode* node, std::ostream& out,
                             std::string code) const
{
    // need to write code
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

HuffmanTree::BinaryNode* HuffmanTree::buildTree(std::string frequencyText)
{
    std::priority_queue<HuffmanTree::BinaryNode*,
                        std::vector<HuffmanTree::BinaryNode*>,
                        compareBinaryNodes>
        nodes;

    // need to write code

    return nodes.top();
}

HuffmanTree::HuffmanTree(std::string frequencyText)
{
    root = buildTree(frequencyText);
    // saveTree(root, string());   // build the lookupTable for codes...can
    // write later
}

HuffmanTree::HuffmanTree(std::ifstream& frequencyStream)
{

    std::string frequencyText(
        (std::istreambuf_iterator<char>(frequencyStream)),
        std::istreambuf_iterator<char>());
    frequencyStream.close();
    if (frequencyText.size() > 0)
    {
        root = buildTree(frequencyText);
        // saveTree(root, string());   // build the lookupTable for codes
    }
}

// print out the char and its encoding
void HuffmanTree::printCodes(std::ostream& out) const
{
    // need to write code
    // calls recursive function
}

// prints out the char and frequency
void HuffmanTree::printTree(std::ostream& out) const
{
    // need to write code
    // calls recursive function
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
