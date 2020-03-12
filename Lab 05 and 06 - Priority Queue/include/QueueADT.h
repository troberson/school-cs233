// Abstract queue class
template <typename E> class Queue
{
  private:
    void operator=(const Queue&)
    {
    } // Protect assignment
    Queue(const Queue&)
    {
    } // Protect copy constructor
  public:
    Queue(){}; // Default
    virtual ~Queue(){}; // Base destructor
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
    virtual const E& frontValue() const = 0;
    // Return: The number of elements in the queue.
    virtual int length() const = 0;
};
