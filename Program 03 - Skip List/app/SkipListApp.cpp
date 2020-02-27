// SkipListApp.cpp : Defines the entry point for the console
// application.
//

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
    int count = 0;
    for (const auto& item : load("csList.txt"))
    {
        list.insert(item->getID(), *item);
        count++;
    }
    std::cout << "Number of Items: " << count << "\n";
    list.displayList();
    std::cout << "\n\nRemove Multiples of 10\n\n";

    // NOLINTNEXTLINE
    for (int i = 10; i < count; i += 10)
    {
        list.remove(i);
        count--;
    }
    list.displayList();

    return 0;
}
