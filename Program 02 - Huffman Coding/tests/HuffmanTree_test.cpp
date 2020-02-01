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


SCENARIO("HuffmanTree: Build Tree finds the most frequent character")
{
    GIVEN("The string 'Hello, World!'")
    {
        HuffmanTree tree{"Hello, World!"};

        THEN("The most common letter is 'l'")
        {
            std::stringstream result{};
            tree.printTree(result);
            REQUIRE(result.str() == "l");
        }
    }
}