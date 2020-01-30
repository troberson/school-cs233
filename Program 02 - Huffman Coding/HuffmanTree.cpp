#include "stdafx.h"
#include "HuffmanTree.h"
#include <string>
#include <vector>
#include <fstream> 
#include <iostream>
#include <queue>    
#include <algorithm>
#include <iomanip> 
#include <bitset>
#include <unordered_map>
#include <sstream>
using namespace std;

inline bool HuffmanTree::getBit(unsigned char byte, int position) const 
{ 
	return (byte  & BITMASK[position]);
}

// Usage
// mybyte = setBit(mybyte,4);
// This sets the bit in position 4
inline unsigned char HuffmanTree::setBit(unsigned char byte, int position) const 
{
	return  byte | BITMASK[position];
}

void HuffmanTree::printBits(char binary, std::ostream & out) const
{
	for (size_t i = 0; i < sizeof(char) * 8; i++) {
		if (getBit(binary, i)) {
			out << 1;
		}
		else {
			out << 0;
		}
	}
}

void HuffmanTree::printBinary(vector<char> bytes, std::ostream & out) const 
{		
	for (char byte : bytes) 
	{
		printBits(byte, out);
		out << "-";		
	}
	
}

string HuffmanTree::getCode(char letter) const 
{	
	string code = "";

	// need to write code
	
	return code;
}

void HuffmanTree::makeEmpty(BinaryNode *& t) {	
	// need to write code
}

void HuffmanTree::printTree(BinaryNode *node, std::ostream & out) const 
{
	// need to write code
}

void HuffmanTree::printCodes(BinaryNode *node, std::ostream & out, string code) const 
{	
	// need to write code
}


void HuffmanTree::saveTree(BinaryNode * current, string code) 
{	
	// need to write code
}

// writes tree information to file so the tree can be rebuilt when unzipping
void HuffmanTree::saveTree(std::ostream & compressedFileStream) 
{
	// need to write code
	// calls recursive function
}


void HuffmanTree::rebuildTree(BinaryNode * node, string element, string codedRoute) 
{
	
	// need to write code

}

void HuffmanTree::rebuildTree(ifstream & compressedFile) {		
	// read info from file
	// use info to build tree
	
	// need to write code
	// calls recursive function
}

HuffmanTree::BinaryNode * HuffmanTree::buildTree(string frequencyText) {
	priority_queue<HuffmanTree::BinaryNode *, 
		           vector<HuffmanTree::BinaryNode *>, 
				   compareBinaryNodes > nodes;
	
	// need to write code	

	return nodes.top();
}

HuffmanTree::HuffmanTree(string frequencyText) 
{
	root = buildTree(frequencyText);
	//saveTree(root, string());   // build the lookupTable for codes...can write later
}

HuffmanTree::HuffmanTree(ifstream & frequencyStream) { 	

	std::string frequencyText( (std::istreambuf_iterator<char>(frequencyStream)),								  std::istreambuf_iterator<char>() );
	frequencyStream.close();
	if (frequencyText.size() > 0) {
		root = buildTree(frequencyText);
		//saveTree(root, string());   // build the lookupTable for codes
	}
}

HuffmanTree::~HuffmanTree() 
{	
	// need to write code	
}

// print out the char and its encoding
void HuffmanTree::printCodes(std::ostream & out) const 
{ 	
	// need to write code
	// calls recursive function
}

// prints out the char and frequency
void HuffmanTree::printTree(std::ostream & out) const 
{	
	// need to write code
	// calls recursive function
}

void HuffmanTree::makeEmpty() 
{	
	// need to write code
	// calls recursive function	
}

string HuffmanTree::decode(vector<char> encodedBytes) {
	string decoded;

	// need to write code
	
	return decoded;
}

vector<char> HuffmanTree::encode(string stringToEncode) 
{
	stringToEncode.push_back(EOFCharacter); // needed when encoding message for file I/O
	
	vector<char> encoded;

	// need to write code
	
	return encoded;
}

void HuffmanTree::uncompressFile(string compressedFileName, 
								 string uncompressedToFileName) {	
	// need to write code	

	// NOTE: when opening the compressedFile, you need to open in 
	//  binary mode for reading..hmmm..why is that?
}

void HuffmanTree::compressFile(string compressToFileName, 
							   string uncompressedFileName, bool buildNewTree) {	
	// need to write code	

	// NOTE: when opening the compressedFile, you need to open in 
	//  binary mode for writing..hmmm..why is that?
}


