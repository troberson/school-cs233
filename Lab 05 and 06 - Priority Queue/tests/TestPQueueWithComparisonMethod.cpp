#include "../Queue/PriorityQueue.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PQueueUnitTest
{
bool compareGreater(int first, int second)
{
    return (first > second);
}

TEST_CLASS(TestPQueueWithComparisonMethod){
    public :
        void static dequeueEmptyList(){
            PriorityQueue<int> pq(compareGreater);
pq.dequeue();
} // namespace PQueueUnitTest

TEST_METHOD(LengthAfterEnqueue)
{
    PriorityQueue<int> pq(compareGreater);
    for (int x = 19; x > 0; x--)
    {
        pq.enqueue(x);
    }

    Assert::AreEqual(19, pq.length(), L"Length not correct after enqueue");
}

TEST_METHOD(LengthAfterDequeue)
{
    PriorityQueue<int> pq(compareGreater);
    for (int x = 19; x > 0; x--)
    {
        pq.enqueue(x);
    }
    pq.dequeue();
    pq.dequeue();
    pq.dequeue();
    pq.dequeue();
    Assert::AreEqual(15, pq.length(), L"Length not correct after enqueue");
}
TEST_METHOD(LengthAfterDequeueEnqueue)
{
    PriorityQueue<int> pq(compareGreater);
    for (int x = 19; x > 0; x--)
    {
        pq.enqueue(x);
    }
    pq.dequeue();
    pq.dequeue();
    pq.dequeue();
    pq.dequeue();
    pq.enqueue(19);
    pq.enqueue(18);
    Assert::AreEqual(17, pq.length(), L"Length not correct after enqueue");
}
}
;
}