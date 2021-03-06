////
// Name: Tamara Roberson
// Section: A
// Program Name: Lab 5 and 6 - Priority Queue
//
// Description: Priority Queue
// A priority queue implemented on top of an array-based binary heap.
// Values are enqueued and sorted with a custom sorter.
// The next value in the queue may be peeked at with frontValue() or
// dequeued.
////


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

SCENARIO("PriorityQueue: Get the front value of an empty list")
{
    GIVEN("An empty list")
    {
        PriorityQueue<int> pq(compareGreater);

        WHEN("Attempting to get the front value")
        {
            THEN("An std::out_of_range exception is thrown")
            {
                REQUIRE_THROWS_AS(pq.frontValue(), std::out_of_range);
            }
        }
    }
}

SCENARIO("PriorityQueue: Enqueing a value to an empty list makes it the "
         "front value")
{
    GIVEN("An empty list")
    {
        PriorityQueue<int> pq(compareGreater);

        WHEN("A value is enqueued")
        {
            pq.enqueue(1);

            THEN("It is the front value")
            {
                REQUIRE(1 == pq.frontValue());
            }
        }
    }
}


SCENARIO("PriorityQueue: After enqueing several items, the highest value "
         "is the front value")
{
    GIVEN("An empty list")
    {
        PriorityQueue<int> pq(compareGreater);

        WHEN("Values are enqueued")
        {
            pq.enqueue(3);
            pq.enqueue(12);
            pq.enqueue(5);
            pq.enqueue(1);
            pq.enqueue(19);

            THEN("The highest value is the front value")
            {
                REQUIRE(19 == pq.frontValue());
            }
        }
    }
}


SCENARIO(
    "PriorityQueue: Items enqueued are dequeued in order (one other item)")
{
    GIVEN("An empty list")
    {
        PriorityQueue<int> pq(compareGreater);

        WHEN("Values are enqueued")
        {
            pq.enqueue(3);
            pq.enqueue(12);

            THEN("The highest value is the front value")
            {
                REQUIRE(12 == pq.frontValue());

                AND_THEN("The highest value is dequeued")
                {
                    REQUIRE(12 == pq.dequeue());

                    AND_THEN("The remaining value is dequeued")
                    {
                        REQUIRE(3 == pq.dequeue());
                    }
                }
            }
        }
    }
}

SCENARIO("PriorityQueue: Items enqueued are dequeued in order (middle "
         "priority last)")
{
    GIVEN("An empty list")
    {
        PriorityQueue<int> pq(compareGreater);

        WHEN("Values are enqueued")
        {
            pq.enqueue(12);
            pq.enqueue(3);
            pq.enqueue(5);

            THEN("The highest value is the front value")
            {
                REQUIRE(12 == pq.frontValue());

                AND_THEN("The highest value is dequeued")
                {
                    REQUIRE(12 == pq.dequeue());

                    AND_THEN("The next highest value is dequeued")
                    {
                        REQUIRE(5 == pq.dequeue());
                        AND_THEN("The remaining value is dequeued")
                        {
                            REQUIRE(3 == pq.dequeue());
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("PriorityQueue: Items enqueued are dequeued in order (lowest "
         "added last)")
{
    GIVEN("An empty list")
    {
        PriorityQueue<int> pq(compareGreater);

        WHEN("Values are enqueued")
        {
            pq.enqueue(3);
            pq.enqueue(1);

            THEN("The highest value is dequeued")
            {
                REQUIRE(3 == pq.dequeue());

                AND_THEN("The remaining value is the front value")
                {
                    REQUIRE(1 == pq.frontValue());
                }
            }
        }
    }
}

SCENARIO("PriorityQueue: Items enqueued are dequeued in order (all items "
         "dequeued)")
{
    GIVEN("An empty list")
    {
        PriorityQueue<int> pq(compareGreater);

        WHEN("Values are enqueued")
        {
            pq.enqueue(3);
            pq.enqueue(12);
            pq.enqueue(5);
            pq.enqueue(1);
            pq.enqueue(19);

            THEN("The highest value is dequeued")
            {
                REQUIRE(19 == pq.dequeue());

                AND_THEN("The next highest value is dequeued")
                {
                    REQUIRE(12 == pq.dequeue());

                    AND_THEN("The next highest value is dequeued")
                    {
                        REQUIRE(5 == pq.dequeue());

                        AND_THEN("The next highest value is dequeued")
                        {
                            REQUIRE(3 == pq.dequeue());

                            AND_THEN("The remaining value is dequeued")
                            {
                                REQUIRE(1 == pq.dequeue());
                            }
                        }
                    }
                }
            }
        }
    }
}


SCENARIO("PriorityQueue: Queue length after enqueuing values is correct")
{
    GIVEN("A priority queue")
    {
        PriorityQueue<int> pq(compareGreater);

        WHEN("19 values are enqueued")
        {
            for (int x = 19; x > 0; x--)
            {
                pq.enqueue(x);
            }

            THEN("The length is 19")
            {
                REQUIRE(19 == pq.length());
            }
        }
    }
}

SCENARIO("PriorityQueue: Queue length after dequeuing values is correct")
{
    GIVEN("A priority queue with 19 values")
    {
        PriorityQueue<int> pq(compareGreater);

        for (int x = 19; x > 0; x--)
        {
            pq.enqueue(x);
        }
        WHEN("4 values are dequeued")
        {
            pq.dequeue();
            pq.dequeue();
            pq.dequeue();
            pq.dequeue();

            THEN("The length is 15")
            {
                REQUIRE(15 == pq.length());
            }
        }
    }
}

SCENARIO("PriorityQueue: Queue length after dequeuing and enqueuing "
         "values is correct")
{
    GIVEN("A priority queue with 19 values")
    {
        PriorityQueue<int> pq(compareGreater);

        for (int x = 19; x > 0; x--)
        {
            pq.enqueue(x);
        }
        WHEN("4 values are dequeued and 2 are enqueued")
        {
            pq.dequeue();
            pq.dequeue();
            pq.dequeue();
            pq.dequeue();
            pq.enqueue(19);
            pq.enqueue(18);

            THEN("The length is 17")
            {
                REQUIRE(17 == pq.length());
            }
        }
    }
}
