#include "stdafx.h"
#include "HuffmanTreeInterface.h"
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>

using namespace std;
class HuffmanTree : HuffmanTreeInterface {
private:
	
	const int BITMASK[8] = { 1 , 2, 4 , 8,  16,  32,  64,  128 };
	class BinaryNode 	{
	public:
		string element;
		int frequency;
		BinaryNode *left;
		BinaryNode *right;
		
		BinaryNode(const string & theElement, int frequency =0, 
				   BinaryNode *left = nullptr, BinaryNode *right = nullptr)
			: element( theElement ), frequency( frequency ), left( left ), right( right)
		{
			// empty constructor
		}
		
		const bool operator < (const BinaryNode &r) const {
			return (frequency < r.frequency);
		}
	};	// end of BinaryNode class

	struct compareBinaryNodes : public binary_function<BinaryNode*, BinaryNode*,bool>
	{
		bool operator() (const BinaryNode* p1, const BinaryNode* p2)
		{
			return p1->frequency > p2->frequency;
		}
	};	// end of compareBinaryNodes struct Functor

	BinaryNode *root = nullptr;
	char EOFCharacter = 0;
	unordered_map<char, string> codeLookup; // can be used to store codes after tree is
											//  created...this is faster than tracing
											//  down the tree each time when encoding a
											//  message.

	void makeEmpty(BinaryNode * &t);
	void printTree(BinaryNode *t, std::ostream & out) const;
	void printCodes(BinaryNode *t, std::ostream & out, string code) const;

	void saveTree(BinaryNode * current, string code);
	void saveTree(std::ostream & out);
	
	void rebuildTree(BinaryNode * node, string element, string codedRoute);
	void rebuildTree(ifstream & file);

	BinaryNode * buildTree(string frequencyText);
	bool getBit(unsigned char byte, int position) const;
	unsigned char setBit(unsigned char byte, int position) const;

public:	
	HuffmanTree(string frequencyText);
	HuffmanTree(ifstream & frequencyStream);
	~HuffmanTree();

	void printTree(std::ostream & out = cout) const;
	void printCodes(std::ostream & out = cout) const;
	void printBinary(vector<char> bytes, std::ostream & out = cout) const;
	void printBits(char binary, std::ostream & out = cout) const;

	string getCode(char letter) const;
	
	void makeEmpty();

	vector<char> encode(string stringToEncode);
	string decode(vector<char> endcodedBytes);	
		
	void uncompressFile(string compressedFileName, string uncompressedToFileName);
	void compressFile(string compressedFileName, string uncompressedFileName,
					  bool buildTree = true);	

};	// end of HuffmanTree class