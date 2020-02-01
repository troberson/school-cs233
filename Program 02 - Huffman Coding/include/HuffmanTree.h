#include "HuffmanTreeInterface.h"

#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class HuffmanTree : HuffmanTreeInterface
{
  private:
    const int BITMASK[8] = {1, 2, 4, 8, 16, 32, 64, 128};

    static constexpr char ASCII_MAX = std::numeric_limits<char>::max();
    static const int ASCII_DEL = 127; // DEL causes an infinite loop

    class BinaryNode
    {
      private:
        std::shared_ptr<BinaryNode> left;
        std::shared_ptr<BinaryNode> right;
        char element;
        int frequency;

      public:
        explicit BinaryNode(char theElement, int frequency = 0,
                            std::shared_ptr<BinaryNode> left = nullptr,
                            std::shared_ptr<BinaryNode> right = nullptr)
            : element(theElement), frequency(frequency),
              left(std::move(left)), right(std::move(right))
        {
        }

        bool operator<(const BinaryNode& rhs) const
        {
            return (frequency < rhs.frequency);
        }

        [[nodiscard]] char getElement() const
        {
            return element;
        }

        [[nodiscard]] int getFrequency() const
        {
            return frequency;
        }

        [[nodiscard]] std::shared_ptr<BinaryNode> getLeft() const
        {
            return left;
        }

        [[nodiscard]] std::shared_ptr<BinaryNode> getRight() const
        {
            return right;
        }
    };

    std::shared_ptr<BinaryNode> root;
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

    std::shared_ptr<BinaryNode> buildTree(std::string frequencyText);
    bool getBit(unsigned char byte, int position) const;
    unsigned char setBit(unsigned char byte, int position) const;

  public:
    explicit HuffmanTree(std::string frequencyText);
    explicit HuffmanTree(std::ifstream& frequencyStream);

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
