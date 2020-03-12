#include "PriorityQueue.h"

#include <catch2/catch.hpp>


bool compareGreater(int first, int second)
{
    return (first > second);
}

SCENARIO("PriorityQueue: Dequeue empty list")
{
    GIVEN("An empty list")
    {
        PriorityQueue<int> pq(compareGreater);

        WHEN("A dequeue is attempted")
        {
            THEN("An std::out_of_range exception is thrown")
            {
                REQUIRE_THROWS_AS(pq.dequeue(), std::out_of_range);
            }
        }
    }
}
