////
// Name: Tamara Roberson
// Section: A
// Program Name: Lab 5 and 6 - Priority Queue
//
// Description: Main app for testing the priority queue
// Enqueues and dequeues random numbers.
// Then enqueues and enqueues Process objects with various sorting schemes.
////

#include "PriorityQueue.h"
#include "Process.h"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using ProcessPtr = std::shared_ptr<Process>;
using ProcessList = std::vector<ProcessPtr>;
using ProcessQueue = PriorityQueue<ProcessPtr>;

std::vector<std::string> split(const std::string& s, char delim)
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

ProcessList load(const std::string& filename)
{
    ProcessList list;
    std::ifstream file(filename);

    std::string str;
    while (std::getline(file, str))
    {
        std::vector<std::string> tokens = split(str, ',');

        list.emplace_back(std::make_shared<Process>(
            tokens[0], stoi(tokens[1]), stoi(tokens[2]),
            static_cast<Process::PriorityLevel>(stoi(tokens[3]))));
    }

    return list;
}

bool compare(int first, int second)
{
    return (first > second);
}

bool compareProcess(ProcessPtr first, ProcessPtr second)
{
    return (first->getPriorityLevel() > second->getPriorityLevel());
}

int main()
{
    srand(time(nullptr));
    int random = 0;

    // Random Numbers
    PriorityQueue<int> pq(
        [](int first, int second) { return (first > second); });

    for (int x = 0; x < 10; x++)
    {
        random = rand() % 10 + 1;
        std::cout << random << " ";
        pq.enqueue(random);
    }
    std::cout << std::endl;

    for (int x = 0; x < 10; x++)
    {
        std::cout << pq.dequeue() << " ";
    }
    std::cout << std::endl;

    // Process with Function Pointer
    ProcessList processes = load("ProcessList.txt");

    for (const auto& process : processes)
    {
        std::cout << (*process) << std::endl;
    }
    std::cout << std::endl;

    // Process Queue with Function Pointer
    ProcessQueue processq(&compareProcess);
    for (const auto& process : processes)
    {
        processq.enqueue(process);
    }
    std::cout << std::endl;

    std::cout << " Start DEQUEUE processq " << std::endl;
    while (processq.length() > 0)
    {
        std::cout << processq.length() << " ";
        std::cout << *(processq.dequeue()) << " ";
        std::cout << std::endl;
    }

    // Process Queue with Lamda
    auto printSorted = [&processes](ProcessQueue& pq) {
        for (auto&& process : processes)
        {
            pq.enqueue(process);
        }

        while (pq.length() > 0)
        {
            std::cout << pq.length() << " " << *(pq.dequeue()) << "\n";
        }
        std::cout << std::endl;
    };

    auto sortPriority = [](const ProcessPtr first,
                           const ProcessPtr second) {
        return (first->getPriorityLevel() > second->getPriorityLevel());
    };
    ProcessQueue pqSortPriority(sortPriority);
    std::cout << "\nStart DEQUEUE processqLambda\n";
    printSorted(pqSortPriority);


    // LAB 6: Lambdas
    // Part 2 A prioritize by ID
    std::cout << "Prioritize by ID\n";
    auto sortID = [](const ProcessPtr first, const ProcessPtr second) {
        return (first->getID() > second->getID());
    };
    ProcessQueue pqSortID(sortID);
    printSorted(pqSortID);

    // Part 2 B prioritize by PriorityLevel Reverse
    std::cout << "Prioritize by PriorityLevel Reverse\n";
    auto sortPriorityReverse = [](const ProcessPtr first,
                                  const ProcessPtr second) {
        return (first->getPriorityLevel() < second->getPriorityLevel());
    };
    ProcessQueue pqSortPriorityReverse(sortPriorityReverse);
    printSorted(pqSortPriorityReverse);


    // Part 2 C prioritize by Size Large to small
    std::cout << "Prioritize by Size\n";
    auto sortSize = [](ProcessPtr first, ProcessPtr second) {
        return (first->getSize() > second->getSize());
    };
    ProcessQueue pqSortSize(sortSize);
    printSorted(pqSortSize);


    // Part 2 D prioritize by Name as in Dictionary
    std::cout << "Prioritize by Name\n";
    auto sortName = [](ProcessPtr first, ProcessPtr second) {
        std::string name1 = first->getName();
        std::string name2 = second->getName();
        auto cmp = [](auto c1, auto c2) {
            return std::tolower(c1) < std::tolower(c2);
        };
        return std::lexicographical_compare(
            name1.begin(), name1.end(), name2.begin(), name2.end(), cmp);
    };
    ProcessQueue pqSortName(sortName);
    printSorted(pqSortName);


    // Part 2 E prioritize by Name Reverse Dictionary
    std::cout << "Prioritize by Name Reverse\n";
    auto sortNameReverse = [](ProcessPtr first, ProcessPtr second) {
        std::string name1 = first->getName();
        std::string name2 = second->getName();
        auto cmp = [](auto c1, auto c2) {
            return std::tolower(c1) > std::tolower(c2);
        };
        return std::lexicographical_compare(
            name1.begin(), name1.end(), name2.begin(), name2.end(), cmp);
    };
    ProcessQueue pqSortNameReverse(sortNameReverse);
    printSorted(pqSortNameReverse);


    // Part 2 F prioritize by PriorityLevel Critcal then High ALL others
    // equal
    std::cout << "Prioritize Critical then High Only\n";
    auto sortCriticalHigh = [](ProcessPtr first, ProcessPtr second) {
        auto p1 = first->getPriorityLevel();
        auto p2 = second->getPriorityLevel();
        return (p1 <= Process::PriorityLevel::High ||
                p2 <= Process::PriorityLevel::High) &&
               p1 < p2;
    };
    ProcessQueue pqSortCriticalHigh(sortCriticalHigh);
    printSorted(pqSortCriticalHigh);

    return 0;
}
