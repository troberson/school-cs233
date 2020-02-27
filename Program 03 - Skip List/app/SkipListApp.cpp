//
// Name: Tamara Roberson
// Section: A
// Program Name: Program 03 - SkipList
//
// Description: An object-oriented implementation of a SkipList, which is a
// variation of a singly-linked list providing random "express lanes" to
// reduce average lookup times. This implementation includes functions for
// inserting, finding, and removing nodes. The nodes are referenced by a
// key, which can be any comparable type.
//
// Like all linked lists, skip lists have poor cache hit performance. This
// implementation is traditional, with downward links but an alternative is
// described here: http://ticki.github.io/blog/skip-lists-done-right/
///


#include "ComputerScientist.h"
#include "SkipList.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::vector<string> split(const string& s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (getline(ss, item, delim))
    {
        tokens.push_back(item);
    }
    return tokens;
}

auto load(const string& filename)
{
    std::vector<ComputerScientist*> list;
    std::ifstream file(filename);

    std::string str;
    while (std::getline(file, str))
    {
        std::vector<string> tokens = split(str, ',');

        list.emplace_back(new ComputerScientist(
            tokens[1], tokens[2], tokens[3], stoi(tokens[0])));
    }

    auto rng = std::mt19937{std::random_device{}()};
    std::shuffle(std::begin(list), std::end(list), rng);
    return list;
}

int main()
{
    SkipList<int, ComputerScientist> list;
    for (const auto& item : load("csList.txt"))
    {
        list.insert(item->getID(), *item);
    }

    int length = list.getLength();
    std::cout << "Number of Items: " << length << "\n";
    list.displayList();
    std::cout << "\n\nRemove Multiples of 10\n\n";


    // NOLINTNEXTLINE
    for (int i = 10; i < length; i += 10)
    {
        list.remove(i);
    }

    std::cout << "Number of Items: " << list.getLength() << "\n";
    list.displayList();

    return 0;
}
