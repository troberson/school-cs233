#include <iostream>
#include <string>


using namespace std;
#include "Process.h"


Process::Process(string name, int processID, int size, PriorityLevel level)
{
    this->name = name;
    this->prioritylevel = level;
    this->processID = processID;
    this->size = size;
}

Process::~Process()
{
}
ostream& operator<<(ostream& os, const Process& p)
{
    os << p.getID() << ' ' << p.getName() << ' '
       << " Level: " << static_cast<int>(p.getPriorityLevel());
    return os;
}
bool operator<(const Process& p1, const Process& p2)
{
    return p1.getPriorityLevel() < p2.getPriorityLevel();
}
int Process::getID() const
{
    return processID;
}

int Process::getSize() const
{
    return size;
}

string Process::getName() const
{
    return this->name;
}

Process::PriorityLevel Process::getPriorityLevel() const
{
    return prioritylevel;
}
