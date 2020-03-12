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

    // Get left node index
    constexpr int leftIndex(int idx)
    {
        return 2 * idx;
    }

    // Get right node index
    constexpr int rightIndex(int idx)
    {
        return 2 * idx + 1;
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
    void print() const
    {
        for (int i = 1; i <= this->count; i++)
        {
            std::cout << "INDEX " << i << ": " << this->items[i] << "\n";
        }
    };

    // Reinitialize the queue. The user is responsible for
    // reclaiming the storage used by the queue elements.
    void clear() override{};

    // Heapify the list using the compareFunction
    void heapify()
    {
        for (int i = this->count / 2; i > 0; i--)
        {
            heapifyRecurse(i);
        }
    }

    void heapifyRecurse(int idx)
    {
        int left = leftIndex(idx);
        int right = rightIndex(idx);
        int max = idx;

        if (left <= this->count &&
            compareFunction(this->items[left], this->items[idx]))
        {
            max = left;
        }

        if (right <= this->count &&
            compareFunction(this->items[right], this->items[idx]))
        {
            max = right;
        }

        if (max != idx)
        {
            std::swap(this->items[idx], this->items[max]);
            heapifyRecurse(max);
        }
    }


    // Place an element at the position
    // based on its prioity of the queue.
    // it: The element being enqueued.
    void enqueue(const E& it) override
    {
        this->items[this->count + 1] = it;
        this->count++;

        heapify();
    }

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

        return this->items[1];
    }

    // Return: The number of elements in the queue.
    [[nodiscard]] int length() const override
    {
        return 0;
    }
};
