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
#include <random>
#include <sstream>
#include <string>
#include <utility>

#include <catch2/catch.hpp>

// A vector of pairs containing a number and a smart pointer to a string
// representation.
using NumList = std::vector<std::pair<int, std::shared_ptr<std::string>>>;

// Generate a list of random numbers
std::vector<int> generateNums(int numValues)
{
    // Set up random number generator
    std::random_device randDevice;
    std::default_random_engine randEngine(randDevice());
    std::uniform_int_distribution<> randNums(1, numValues);
    auto rnd = std::bind(randNums, randEngine);

    // Function to check if the number list already contains a given value
    auto contains = [](const auto& l, const auto val) {
        return std::find(l.begin(), l.end(), val) != l.end();
    };

    // Create number list
    std::vector<int> nums(numValues);

    // Generate values
    for (auto& node : nums)
    {
        int n = rnd();
        while (contains(nums, n))
        {
            n = rnd();
        }
        node = n;
    }

    // Return
    return nums;
}

// Generate a NumList containing pairs of numbers and their string
// representation
NumList generatePairs(std::vector<int> nums)
{
    NumList numPairs;
    std::transform(
        nums.begin(), nums.end(), std::back_inserter(numPairs), [](int n) {
            auto str = std::make_shared<std::string>(std::to_string(n));
            return std::make_pair(n, str);
        });
    return numPairs;
}

// Generate a tree from a list of numbers
// NOTE: The returned NumList of pairs must be kept alive as long as the
// tree is, since the tree only takes raw pointers.
auto generateTree(std::vector<int> nums)
{
    // Create the tree
    BinarySearchTree<int, std::string*> tree;

    // Create the list of pairs
    NumList pairs = generatePairs(nums);
    for (auto& [n, str] : pairs)
    {
        tree.insert(str.get(), n);
    }

    // Return
    return std::make_pair(tree, pairs);
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


SCENARIO("BSTree: Grow Tree")
{
    GIVEN("A tree with 30 random values")
    {
        const int numValues = 30;

        auto [tree, nums] = generateTree(numValues);

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
        const int numValues = 30;

        auto [tree, nums] = generateTree(numValues);

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
