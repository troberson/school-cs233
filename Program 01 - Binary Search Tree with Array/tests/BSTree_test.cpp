////
// Name: Tamara Roberson
// Section: A
// Program Name: Program 1 - Binary Search Tree with Array
//
// Description: A Binary Search Tree implemented as an array.
////

#include <BSTree.h>

#include <memory>
#include <sstream>
#include <string>

#include <catch2/catch.hpp>

SCENARIO("BSTree: Create an empty tree")
{
    GIVEN("An empty tree")
    {
        BinarySearchTree<int, int*> tree;

        THEN("The count is 0")
        {
            REQUIRE(0 == tree.getCount());
        }

        THEN("The size is 25")
        {
            REQUIRE(25 == tree.getSize());
        }
    }
}


SCENARIO("BSTree: Add item to a tree")
{
    GIVEN("An empty tree")
    {
        BinarySearchTree<int, std::string*> tree;
        auto stringOne = std::make_unique<std::string>("One");
        auto stringTwo = std::make_unique<std::string>("Two");
        auto stringThree = std::make_unique<std::string>("Three");

        WHEN("A string 'One' is added")
        {
            tree.insert(stringOne.get(), 1);

            THEN("The count is 1")
            {
                REQUIRE(1 == tree.getCount());
            }

            AND_WHEN("The string 'Three' is added")
            {
                tree.insert(stringThree.get(), 3);

                THEN("The count is 2")
                {
                    REQUIRE(2 == tree.getCount());
                }

                AND_WHEN("The string 'Two' is added")
                {
                    tree.insert(stringTwo.get(), 2);

                    THEN("The count is 3")
                    {
                        REQUIRE(3 == tree.getCount());
                    }

                    AND_THEN(
                        "The string representation is 'One Two Three'")
                    {
                        std::ostringstream result;
                        tree.printTree(result);

                        std::ostringstream expected;
                        expected << *stringOne << "\n"
                                 << *stringTwo << "\n"
                                 << *stringThree << "\n";

                        REQUIRE(result.str() == expected.str());
                    }
                }
            }
        } // end WHEN
    } // end GIVEN
} // end SCENARIO
