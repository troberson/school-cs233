#pragma once

// Abstract queue class
template <typename E>
class Queue
{
  public:
    // Protect assignment
    void operator=(const Queue&) = delete;

    // Protect copy constructor
    Queue(const Queue&) = delete;

	// Default constructor
    Queue() = default;

	// Base destructor
    virtual ~Queue() = default;

    // Reinitialize the queue. The user is responsible for
    // reclaiming the storage used by the queue elements.
    virtual void clear() = 0;

    // Place an element at the position
    // based on its prioity of the queue.
    // it: The element being enqueued.
    virtual void enqueue(const E& it) = 0;

    // Remove and return element at the front of the queue.
    // Return: The element at the front of the queue.
    virtual E dequeue() = 0;

    // Return: A copy of the front element.
    [[nodiscard]] virtual const E& frontValue() const = 0;

    // Return: The number of elements in the queue.
    [[nodiscard]] virtual int length() const = 0;
};
