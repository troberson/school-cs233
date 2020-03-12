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
    constexpr int getLeft(int idx)
    {
        return 2 * idx;
    }

    // Get right node index
    constexpr int getRight(int idx)
    {
        return 2 * idx + 1;
    }

    // Get parent index
    constexpr int getParent(int idx)
    {
        return idx / 2;
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
    void heapifyUp(int idx)
    {
        int parent = getParent(idx);

        if (idx > 1 &&
            compareFunction(this->items[idx], this->items[parent]))
        {
            std::swap(this->items[idx], this->items[parent]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int idx)
    {
        int left = getLeft(idx);
        int right = getRight(idx);
        int max = idx;

        if (left <= this->count &&
            compareFunction(this->items[left], this->items[max]))
        {
            max = left;
        }

        if (right <= this->count &&
            compareFunction(this->items[right], this->items[max]))
        {
            max = right;
        }

        if (max != idx)
        {
            std::swap(this->items[idx], this->items[max]);
            heapifyDown(max);
        }
    }


    // Place an element at the position
    // based on its prioity of the queue.
    // it: The element being enqueued.
    void enqueue(const E& it) override
    {
        this->items[this->count + 1] = it;
        this->count++;

        heapifyUp(this->count);
    }

    // Remove and return element at the front of the queue.
    // Return: The element at the front of the queue.
    E dequeue() override
    {
        assertNotEmpty();

        std::swap(this->items[this->count], this->items[1]);
        this->count--;

        heapifyDown(1);
        return this->items[this->count + 1];
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
