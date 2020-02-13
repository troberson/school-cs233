#include "HuffmanTreeInterface.h"

#include <bitset>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class HuffmanTree : HuffmanTreeInterface
{
  private:
    static constexpr char CHAR_MAX = std::numeric_limits<char>::max();
    static const int ASCII_DEL = 127; // DEL causes an infinite loop
    static constexpr int CHAR_WIDTH =
        std::numeric_limits<char>::digits + 1;
    static constexpr int CODE_WIDTH = CHAR_MAX;

    class BinaryNode
    {
      private:
        std::shared_ptr<BinaryNode> left;
        std::shared_ptr<BinaryNode> right;
        char element;
        int frequency;

      public:
        explicit BinaryNode(char theElement = 0, int frequency = 0,
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

        bool operator>(const BinaryNode& rhs) const
        {
            return (frequency > rhs.frequency);
        }

        [[nodiscard]] char getElement() const
        {
            return element;
        }

        [[nodiscard]] int getFrequency() const
        {
            return frequency;
        }

        [[nodiscard]] BinaryNode* getLeft() const
        {
            return this->left.get();
        }

        [[nodiscard]] BinaryNode* getRight() const
        {
            return this->right.get();
        }

        void setLeft(std::shared_ptr<BinaryNode> node)
        {
            this->left = std::move(node);
        }

        void setRight(std::shared_ptr<BinaryNode> node)
        {
            this->right = std::move(node);
        }

        [[nodiscard]] bool isLeaf()
        {
            return this->left == nullptr && this->right == nullptr;
        }

        std::string str()
        {
            // Example:
            // Leaf: 'x' (3)
            // Internal: (Internal) (12)
            char c = this->element;

            std::stringstream out;
            out << "  ";
            if (c > 0)
            {
                out << "'" << c << "'";
            }
            else
            {
                out << "(Internal - ";

                std::function<void(BinaryNode*)> printSubtree =
                    [&](BinaryNode* node) {
                        if (node == nullptr)
                        {
                            return;
                        }
                        printSubtree(node->getLeft());
                        if (node->isLeaf())
                        {
                            out << node->getElement();
                        }
                        printSubtree(node->getRight());
                    };

                printSubtree(this);

                out << ")";
            }
            out << " (" << this->frequency << ")";

            return out.str();
        }
    };

    std::shared_ptr<BinaryNode> root;
    char EOFCharacter = 0;

    // can be used to store codes after tree is
    //  created...this is faster than tracing
    //  down the tree each time when encoding a
    //  message.

    std::unordered_map<char, std::string> codeLookup;
    void
    buildTable(BinaryNode* node,
               std::bitset<CODE_WIDTH> bits = std::bitset<CODE_WIDTH>{},
               int depth = 0);

    std::string codebook;

    std::map<int, std::map<std::string, char>> decodeTable;

    void makeEmpty(BinaryNode* node);
    void printTree(BinaryNode* node, std::ostream& out) const;
    void printCodes(BinaryNode* node, std::ostream& out) const;

    std::string saveTable();

    std::unordered_map<char, std::string>
    rebuildTable(const std::string& codebookStr);

    auto makeDecodeTable(std::unordered_map<char, std::string> codeLookup);

    std::shared_ptr<BinaryNode>
    buildTree(const std::string& frequencyText);

    std::shared_ptr<BinaryNode> buildTree(std::istream& frequencyStream);

    std::unordered_map<char, std::string>
    makeCanonical(std::unordered_map<char, std::string> oldTable);

    std::unordered_map<char, std::string>
    makeCodebook(const std::vector<std::pair<char, int>>& bitLengths);

    void build(const std::string& frequencyText);
    void build(std::ifstream& frequencyStream);

  public:
    explicit HuffmanTree(const std::string& frequencyText);
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
