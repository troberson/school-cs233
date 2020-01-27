////
// Name: Tamara Roberson
// Section: A
// Program Name: Program 1 - Binary Search Tree with Array
//
// Description: A Binary Search Tree implemented as an array.
////

#include <BSTree.h>

#include <algorithm>
#include <memory>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <utility>

#include <catch2/catch.hpp>

// A vector of pairs containing a number and a pointer to a string
// representation.
using NumList = std::vector<std::pair<int, std::string*>>;

// The tree representation of the data in a NumList
using NumTree = BinarySearchTree<int, string*>;

// Generate a randomized list of numbers from 1 to maxVal
std::vector<int> generateNums(int maxVal)
{
    // Create list of numbers
    std::vector<int> nums(maxVal);

    // Fill list with numbers 1 to maxVal
    std::iota(nums.begin(), nums.end(), 1);

    // Shuffle the number list
    std::shuffle(nums.begin(), nums.end(),
                 std::mt19937{std::random_device{}()});

    // Return
    return nums;
}


// Generate a NumList containing pairs of numbers and their string
// representation
NumList generatePairs(const std::vector<int>& nums)
{
    NumList numPairs;
    for (auto& n : nums)
    {
        auto str = new std::string(std::to_string(n));
        numPairs.emplace_back(std::make_pair(n, str));
    }
    return numPairs;
}

// Generate a tree from a list of numbers
auto generateTree(const std::vector<int>& nums)
{
    // Create the tree
    BinarySearchTree<int, std::string*> tree;

    // Create the list of pairs
    NumList pairs = generatePairs(nums);
    for (auto& [n, str] : pairs)
    {
        tree.insert(str, n);
    }

    // Return
    return tree;
}

// Generate a tree with a given number of random values.
auto generateTree(int numValues)
{
    return generateTree(generateNums(numValues));
}

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


SCENARIO("BSTree: Add items to a tree")
{
    GIVEN("An empty tree")
    {
        BinarySearchTree<int, std::string*> tree;
        auto stringOne = new std::string("One");
        auto stringTwo = new std::string("Two");
        auto stringThree = new std::string("Three");

        WHEN("A string 'One' is added")
        {
            tree.insert(stringOne, 1);

            THEN("The count is 1")
            {
                REQUIRE(1 == tree.getCount());

                AND_WHEN("The string 'Three' is added")
                {
                    tree.insert(stringThree, 3);

                    THEN("The count is 2")
                    {
                        REQUIRE(2 == tree.getCount());
                    }

                    AND_WHEN("The string 'Two' is added")
                    {
                        tree.insert(stringTwo, 2);

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
            } // end GIVEN
        } // end WHEN
    } // end GIVEN
} // end SCENARIO


SCENARIO("BSTree: Grow Tree")
{
    GIVEN("A tree with 30 random values")
    {
        const int numValues = 30;
        auto tree = generateTree(numValues);

        THEN("The count is 30")
        {
            REQUIRE(numValues == tree.getCount());

            AND_THEN("The size is at least 30")
            {
                REQUIRE(numValues <= tree.getSize());
            }
        }
    }
}

SCENARIO("BSTree: Find Minimum and Maximum Value")
{
    GIVEN("A tree with values from 1-30")
    {
        auto tree = generateTree(30);

        THEN("The minimum value is 1")
        {
            std::string minVal = *tree.findMin();
            REQUIRE("1" == minVal);
        }

        THEN("The maximum value is 30")
        {
            std::string maxVal = *tree.findMax();
            REQUIRE("30" == maxVal);
        }
    }
}


SCENARIO("BSTree: Find values")
{
    GIVEN("A tree with values from 1-5")
    {
        auto tree = generateTree(5);

        THEN("The key 4 exists in the tree")
        {
            REQUIRE(tree.contains(4));
        }

        THEN("The key 6 does not exist in the tree")
        {
            REQUIRE_FALSE(tree.contains(6));
        }

        THEN("The value from key 3 is extracted")
        {
            std::string* result;
            tree.find(3, result);
            REQUIRE("3" == *result);
        }

        THEN("Extracting the value from key 7 fails")
        {
            std::string* result;
            REQUIRE_FALSE(tree.find(7, result));
        }
    }
}


SCENARIO("BSTree: Make an existing tree empty")
{
    GIVEN("A tree with values 1-30")
    {
        const int numValues = 30;
        auto tree = generateTree(numValues);

        THEN("The count is 30")
        {
            REQUIRE(numValues == tree.getCount());
        }

        THEN("The size is at least 30")
        {
            REQUIRE(numValues <= tree.getSize());
        }

        WHEN("The tree is emptied")
        {
            tree.makeEmpty();

            THEN("The tree is empty")
            {
                REQUIRE(tree.isEmpty());
            }

            THEN("The count is 0")
            {
                REQUIRE(0 == tree.getCount());
            }

            THEN("The size is the default (25)")
            {
                REQUIRE(NumTree::DEFAULT_SIZE == tree.getSize());
            }
        }
    }
}


SCENARIO("BSTree: Delete a key")
{
    GIVEN("A tree with values 1-10")
    {
        const int numValues = 10;
        auto tree = generateTree(numValues);

        THEN("The count is 10")
        {
            REQUIRE(numValues == tree.getCount());


            WHEN("The key 5 is deleted")
            {
                tree.remove(5);

                THEN("The count is 9")
                {
                    REQUIRE(numValues - 1 == tree.getCount());
                }
            }

            WHEN("The non-existent key 11 is deleted")
            {
                tree.remove(11);

                THEN("The count remains 10")
                {
                    REQUIRE(numValues == tree.getCount());
                }
            }
        }
    }
}
