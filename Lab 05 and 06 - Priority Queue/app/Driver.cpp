#include "PriorityQueue.h"
#include "Process.h"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

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

std::vector<Process*> load(const std::string& filename)
{
    std::vector<Process*> list;
    std::ifstream file(filename);

    std::string str;
    while (std::getline(file, str))
    {
        std::vector<std::string> tokens = split(str, ',');

        list.push_back(new Process(
            tokens[0], stoi(tokens[1]), stoi(tokens[2]),
            static_cast<Process::PriorityLevel>(stoi(tokens[3]))));
    }

    return list;
}

bool compare(int first, int second)
{
    return (first > second);
}

bool compareProcess(Process* first, Process* second)
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
    std::vector<Process*> processes = load("ProcessList.txt");
    for (Process* process :
         processes) // access by reference to avoid copying
    {
        std::cout << (*process) << std::endl;
    }
    std::cout << std::endl;

    // Process Queue with Function Pointer
    PriorityQueue<Process*> processq(&compareProcess);
    for (Process* process :
         processes) // access by reference to avoid copying
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
    auto printSorted = [&processes](PriorityQueue<Process*>& pq) {
        for (Process* process : processes)
        {
            pq.enqueue(process);
        }

        while (pq.length() > 0)
        {
            std::cout << pq.length() << " " << *(pq.dequeue()) << "\n";
        }
        std::cout << std::endl;
    };

    auto sortPriority = [](Process* first, Process* second) {
        return (first->getPriorityLevel() > second->getPriorityLevel());
    };
    PriorityQueue<Process*> pqSortPriority(sortPriority);
    std::cout << "\nStart DEQUEUE processqLambda\n";
    printSorted(pqSortPriority);


    // LAB 6: Lambdas
    // Part 2 A prioritize by ID
    std::cout << "Prioritize by ID\n";
    auto sortID = [](Process* first, Process* second) {
        return (first->getID() > second->getID());
    };
    PriorityQueue<Process*> pqSortID(sortID);
    printSorted(pqSortID);


    // Part 2 B prioritize by PriorityLevel Reverse
    std::cout << "Prioritize by PriorityLevel Reverse\n";
    auto sortPriorityReverse = [](Process* first, Process* second) {
        return (first->getPriorityLevel() < second->getPriorityLevel());
    };
    PriorityQueue<Process*> pqSortPriorityReverse(sortPriorityReverse);
    printSorted(pqSortPriorityReverse);


    // Part 2 C prioritize by Size Large to small
    std::cout << "Prioritize by Size\n";
    auto sortSize = [](Process* first, Process* second) {
        return (first->getSize() > second->getSize());
    };
    PriorityQueue<Process*> pqSortSize(sortSize);
    printSorted(pqSortSize);


    // Part 2 D prioritize by Name as in Dictionary
    std::cout << "Prioritize by Name\n";
    auto sortName = [](Process* first, Process* second) {
        std::string name1 = first->getName();
        std::string name2 = second->getName();
        auto cmp = [](auto c1, auto c2) {
            return std::tolower(c1) < std::tolower(c2);
        };
        return std::lexicographical_compare(
            name1.begin(), name1.end(), name2.begin(), name2.end(), cmp);
    };
    PriorityQueue<Process*> pqSortName(sortName);
    printSorted(pqSortName);


    // Part 2 E prioritize by Name Reverse Dictionary
    std::cout << "Prioritize by Name Reverse\n";
    auto sortNameReverse = [](Process* first, Process* second) {
        std::string name1 = first->getName();
        std::string name2 = second->getName();
        auto cmp = [](auto c1, auto c2) {
            return std::tolower(c1) > std::tolower(c2);
        };
        return std::lexicographical_compare(
            name1.begin(), name1.end(), name2.begin(), name2.end(), cmp);
    };
    PriorityQueue<Process*> pqSortNameReverse(sortNameReverse);
    printSorted(pqSortNameReverse);


    // Part 2 F prioritize by PriorityLevel Critcal then High ALL others
    // equal
    std::cout << "Prioritize Critical Only\n";
    auto sortCritical = [](Process* first, Process* second) {
        return first->getPriorityLevel() ==
               Process::PriorityLevel::Critical;
    };
    PriorityQueue<Process*> pqSortCritical(sortCritical);
    printSorted(pqSortCritical);

    return 0;
}
