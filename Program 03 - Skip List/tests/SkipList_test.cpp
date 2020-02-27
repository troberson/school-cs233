///
// Name: Tamara Roberson
// Section: A
// Program Name: Program 03 - SkipList
//
// Description: An object-oriented implementation of a SkipList, which is a
// variation of a singly-linked list providing random "express lanes" to
// reduce average lookup times. This implementation includes functions for
// inserting, finding, and removing nodes. The nodes are referenced by a
// key, which can be any comparable type.
///

#include "SkipList.h"

#include <iostream>
#include <sstream>
#include <string>

#include <catch2/catch.hpp>

SCENARIO("Create an empty Skip List")
{
    GIVEN("An empty Skip List")
    {
        SkipList<int, int> list;

        THEN("The length is 0")
        {
            REQUIRE(0 == list.getLength());
        }

        AND_THEN("Nothing is displayed when the output is shown")
        {
            std::stringstream result;
            list.displayList(result);
            REQUIRE(result.str().empty());
        }
    }
}

SCENARIO("Create an single-item Skip List")
{
    GIVEN("An empty Skip List")
    {
        SkipList<int, int> list;

        WHEN("An item is inserted")
        {
            list.insert(1, 1);

            THEN("The length is 1")
            {
                REQUIRE(1 == list.getLength());
            }

            AND_THEN("The item is listed when the output is shown")
            {
                std::stringstream result;
                list.displayList(result);
                REQUIRE(result.str() == "L0: 1 \n");
            }
        }
    }
}