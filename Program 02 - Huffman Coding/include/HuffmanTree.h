#include "HuffmanTreeInterface.h"
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class HuffmanTree : HuffmanTreeInterface
{
  private:
    const int BITMASK[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    class BinaryNode
    {
      public:
        std::string element;
        int frequency;
        BinaryNode* left;
        BinaryNode* right;

        explicit BinaryNode(const std::string& theElement,
                            int frequency = 0, BinaryNode* left = nullptr,
                            BinaryNode* right = nullptr)
            : element(theElement), frequency(frequency), left(left),
              right(right)
        {
            // empty constructor
        }

        bool operator<(const BinaryNode& r) const
        {
            return (frequency < r.frequency);
        }
    }; // end of BinaryNode class

    struct compareBinaryNodes
        : public std::binary_function<BinaryNode*, BinaryNode*, bool>
    {
        bool operator()(const BinaryNode* p1, const BinaryNode* p2)
        {
            return p1->frequency > p2->frequency;
        }
    }; // end of compareBinaryNodes struct Functor

    BinaryNode* root = nullptr;
    char EOFCharacter = 0;

    // can be used to store codes after tree is
    //  created...this is faster than tracing
    //  down the tree each time when encoding a
    //  message.

    std::unordered_map<char, std::string> codeLookup;
    void makeEmpty(BinaryNode*& node);
    void printTree(BinaryNode* node, std::ostream& out) const;
    void printCodes(BinaryNode* node, std::ostream& out,
                    std::string code) const;

    void saveTree(BinaryNode* current, std::string code);
    void saveTree(std::ostream& compressedFileStream);

    void rebuildTree(BinaryNode* node, std::string element,
                     std::string codedRoute);
    void rebuildTree(std::ifstream& file);

    BinaryNode* buildTree(std::string frequencyText);
    bool getBit(unsigned char byte, int position) const;
    unsigned char setBit(unsigned char byte, int position) const;

  public:
    explicit HuffmanTree(std::string frequencyText);
    explicit HuffmanTree(std::ifstream& frequencyStream);
    ~HuffmanTree();

    void printTree(std::ostream& out = std::cout) const override;
    void printCodes(std::ostream& out = std::cout) const override;
    void printBinary(std::vector<char> bytes,
                     std::ostream& out = std::cout) const;
    void printBits(char binary, std::ostream& out = std::cout) const;

    std::string getCode(char letter) const override;

    void makeEmpty() override;

    std::vector<char> encode(std::string stringToEncode) override;
    std::string decode(std::vector<char> encodedBytes) override;

    void uncompressFile(std::string compressedFileName,
                        std::string uncompressToFileName) override;
    void compressFile(std::string compressToFileName,
                      std::string uncompressedFileName,
                      bool buildNewTree = true) override;

}; // end of HuffmanTree class
