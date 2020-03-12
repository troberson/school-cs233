#include "QueueADT.h"

#include <iostream>
#include <stdexcept>

template <typename E> class PriorityQueue : Queue<E>
{
  private:
    E* items;
    unsigned int count = 0; // number of items
    bool (*compareFunction)(E, E);

    // Intialization helper method
    void init()
    {
        this->items = new E[10]();
        this->count = 0;
    }

    // Return link nodes to free store
    void removeall()
    {
    }

    // Is the queue empty?
    [[nodiscard]] bool isEmpty() const
    {
        return this->count == 0;
    }

    // Throw std::out_of_range exception if the queue is empty.
    void assertNotEmpty() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Queue is empty");
        }
    }


  public:
    // Protect assignment
    void operator=(const PriorityQueue&) = delete;

    // Protect copy constructor
    PriorityQueue(const PriorityQueue&) = delete;

    // takes a function pointer to a compare function
    // as a Parameter
    explicit PriorityQueue(bool (*func)(E, E))
    {
        compareFunction = func;
        init();
    }

    // Base destructor
    ~PriorityQueue() override = default;

    // Print queue contents
    void print() const {};

    // Reinitialize the queue. The user is responsible for
    // reclaiming the storage used by the queue elements.
    void clear() override{};

    // Place an element at the position
    // based on its prioity of the queue.
    // it: The element being enqueued.
    void enqueue(const E& it) override{};

    // Remove and return element at the front of the queue.
    // Return: The element at the front of the queue.
    E dequeue() override
    {
        assertNotEmpty();

        return E();
    }

    // Return: A copy of the front element.
    [[nodiscard]] const E& frontValue() const override
    {
        assertNotEmpty();

        return E();
    }

    // Return: The number of elements in the queue.
    [[nodiscard]] int length() const override
    {
        return 0;
    }
};
