// HuffmanCoding.cpp : Defines the entry point for the console application.
//
#include "HuffmanTree.h"

#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <streambuf>
#include <string>
#include <unordered_map>


int main()
{
    // // example code for priority_queue....play with it and then
    // // remove/comment out
    // std::cout << "priority_queue test area: \n";
    // std::priority_queue<int, std::vector<int>, std::greater<>> pq;

    // pq.push(111); // NOLINT(readability-magic-numbers,
    // cppcoreguidelines-avoid-magic-numbers) pq.push(1111); //
    // NOLINT(readability-magic-numbers,
    // cppcoreguidelines-avoid-magic-numbers) pq.push(1011); //
    // NOLINT(readability-magic-numbers,
    // cppcoreguidelines-avoid-magic-numbers) pq.push(100); //
    // NOLINT(readability-magic-numbers,
    // cppcoreguidelines-avoid-magic-numbers) pq.push(1110); //
    // NOLINT(readability-magic-numbers,
    // cppcoreguidelines-avoid-magic-numbers) pq.push(101); //
    // NOLINT(readability-magic-numbers,
    // cppcoreguidelines-avoid-magic-numbers)

    // std::cout << "Top: " << pq.top() << std::endl;
    // pq.push(10); // NOLINT(readability-magic-numbers,
    // cppcoreguidelines-avoid-magic-numbers) std::cout << "New Top: " <<
    // pq.top() << std::endl;

    // while (!pq.empty())
    // {
    //     std::cout << pq.top() << std::endl;
    //     pq.pop();
    // }
    // std::cout << std::endl << std::endl;

    // // example code for unordered_map....play with it and then
    // // remove/comment out
    // //  an unordered_map can be used to store the char and its encoded
    // //  values after you have built the tree
    // std::cout << "unordered_map test area: \n";
    // std::unordered_map<char, std::string> exampleMap;
    // exampleMap['a'] = "apple";
    // exampleMap['b'] = "ballon";
    // exampleMap['c'] = "compiler";
    // exampleMap['d'] = "10010";

    // std::cout << "c has: " << exampleMap['c'] << std::endl;

    // exampleMap['c'] = "changed";
    // for (const auto& pair : exampleMap)
    // {
    //     std::cout << pair.first << " = " << pair.second << std::endl;
    // }
    // std::cout << "Number of items stored in map: " << exampleMap.size();
    // std::cout << std::endl << std::endl;


    // SUGGESTION: write and test the functions in the order called below
    //         (some of the functions may need to call other private
    //         functions)

    // Test 1
    // cout << "\n\nTest 1\n";
    std::cout << "\n\nBuilding the tree from: HHHHEELLLLLLLOO "
                 "WOOOOORRLLLLLLDP\n";

    HuffmanTree tree("HHHHEELLLLLLLOO WOOOOORRLLLLLLDP");

    std::cout << "\n\nprintTree: \n";
    tree.printTree();

    std::cout << "\n\nprintCodes:\n";
    tree.printCodes();
    std::cout << std::endl << std::endl;

    std::cout << "Code L :" << tree.getCode('L') << std::endl;
    std::cout << "Code D :" << tree.getCode('D') << std::endl;


    // Test 2
    // cout << "\n\nTest 2\n";
    // vector<char> encoded = tree.encode("HELP");
    // tree.printCodes();
    // tree.printBinary(encoded);
    // cout << endl;
    //
    // cout << tree.decode(encoded) << ":" << endl;
    // system("pause");

    // Test 3
    // cout << "\n\nTest 3\n";
    // std::ifstream frequencyStream("Bigo.txt");
    // HuffmanTree tree2(frequencyStream);
    // tree2.printTree();
    // tree2.printCodes();

    // tree2.compressFile("BigO.bin", "Bigo.txt");
    // tree2.printCodes();
    // tree2.uncompressFile("BigO.bin", "BigORebuilt.txt");
    // tree2.printTree();
    // tree2.printCodes();

    ////Test 4
    // cout << "\n\nTest 4\n";
    // std::ifstream frequencyStream2("20000leagues.txt");
    // HuffmanTree tree3(frequencyStream2);
    // tree3.printTree();
    // tree3.printCodes();
    // cout << "Code L :" << tree3.getCode('L') << endl;
    // tree3.compressFile("20000leaguesComp.bin" ,"20000leagues.txt",true);
    // tree3.uncompressFile("20000leaguesComp.bin",
    // "20000leaguesRebuilt.txt"); tree3.printTree(); tree3.printCodes();

    // Try Other Files

    //// read in text file create string - might be useful
    // std::ifstream bigtext("20000leagues.txt");
    // std::string big((std::istreambuf_iterator<char>(bigtext)),
    //				   std::istreambuf_iterator<char>());

    std::cout << std::endl;
    return 0;
}
