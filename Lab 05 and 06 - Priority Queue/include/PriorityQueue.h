#include "QueueADT.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename E> class PriorityQueue : Queue<E>
{
  private:
    E* items;
    unsigned int count = 0; // number of items
    bool (*compareFunction)(E, E);
    // Protect assignment
    void operator=(const PriorityQueue&){

    };
    // Protect copy constructor
    PriorityQueue(const PriorityQueue&){

    };
    // Intialization helper method
    void init()
    {
        this->items = new E[10]();
        this->count = 0;
    }
    void removeall()
    { // Return link nodes to free store
    }

  public:
    // takes a function pointer to a compare function
    // as a Parameter
    PriorityQueue(bool (*func)(E, E))
    {
        compareFunction = func;
        init();
    }

    // Print queue contents
    void print() const {


    };

    // Base destructor
    ~PriorityQueue()
    {
    }
    // Reinitialize the queue. The user is responsible for
    // reclaiming the storage used by the queue elements.
    void clear(){

    };
    // Place an element at the position
    // based on its prioity of the queue.
    // it: The element being enqueued.
    void enqueue(const E& it){


    };
    // Remove and return element at the front of the queue.
    // Return: The element at the front of the queue.
    E dequeue()
    {
        return E();
    };
    // Return: A copy of the front element.
    const E& frontValue() const
    {
        return E();
    }
    // Return: The number of elements in the queue.
    int length() const
    {
        return 0;
    }
};