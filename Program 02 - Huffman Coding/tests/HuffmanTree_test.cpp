////
// Name: Tamara Roberson
// Section: A
// Program Name: Program 2 - Huffman Encoding
//
// Description: A compression algorithm using Huffman encoding
////

#include "HuffmanTree.h"

#include <iostream>
#include <sstream>
#include <string>

#include <catch2/catch.hpp>


SCENARIO("HuffmanTree: Tree contains the character frequencies")
{
    GIVEN("The string 'Hello, World!'")
    {
        HuffmanTree tree{"Hello, World!"};

        std::stringstream result_stream{};
        tree.printTree(result_stream);

        // The tree uses weak ordering, so trees will not necessarily be
        // the same every time. But we can check for the correct
        // frequencies.
        THEN("The tree contains the correct frequencies.")
        {
            std::string result = result_stream.str();

            auto contains = [&result](char c, int f) {
                std::stringstream substr;
                substr << "'" << c << "' (" << f << ")";

                return result.find(substr.str()) != std::string::npos;
            };

            REQUIRE(contains('H', 1));
            REQUIRE(contains('e', 1));
            REQUIRE(contains('l', 3));
            REQUIRE(contains('o', 2));
            REQUIRE(contains(',', 1));
            REQUIRE(contains(' ', 1));
            REQUIRE(contains('W', 1));
            REQUIRE(contains('r', 1));
            REQUIRE(contains('d', 1));
            REQUIRE(contains('!', 1));
        }
    }
}
