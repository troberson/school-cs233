#pragma once
#include <string>
class Process
{

  public:
    enum class PriorityLevel
    {
        Critical,
        High,
        Mediumn,
        Low

    };
    Process(std::string name, int processID, int size, PriorityLevel level);
    ~Process();

    [[nodiscard]] int getID() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] PriorityLevel getPriorityLevel() const;
    friend std::ostream& operator<<(std::ostream& os, const Process& p);
    friend bool operator<(const Process& p1, const Process& p2);

  private:
    std::string name;
    int processID;
    int size = 0;
    PriorityLevel prioritylevel;
};
