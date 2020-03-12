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
    PriorityQueue<Process*> processqLambda([](Process* first,
                                              Process* second) {
        return (first->getPriorityLevel() > second->getPriorityLevel());
    });

    for (Process* process :
         processes) // access by reference to avoid copying
    {
        processqLambda.enqueue(process);
    }
    std::cout << std::endl;

    std::cout << " Start DEQUEUE processqLambda " << std::endl;
    while (processqLambda.length() > 0)
    {
        std::cout << processqLambda.length() << " ";
        std::cout << *(processqLambda.dequeue()) << " ";
        std::cout << std::endl;
    }

    // Part 2 A prioritize by ID

    // Part 2 B prioritize by PriorityLevel Reverse

    // Part 2 C prioritize by Size Large to small

    // Part 2 D prioritize by Name as in Dictionary

    // Part 2 E prioritize by Name Reverse Dictionary

    // Part 2 F prioritize by PriorityLevel Critcal then High ALL others
    // equal

    return 0;
}
