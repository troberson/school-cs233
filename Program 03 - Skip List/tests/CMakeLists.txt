# Testing library
FetchContent_Declare(
catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG        v2.9.1
)
FetchContent_MakeAvailable(catch2)

add_executable(skiplist_test
    test_main.cpp
    SkipList_test.cpp
)

# Use C++17
target_compile_features(skiplist_test PRIVATE cxx_std_17)

# Link to main library and Catch2
target_link_libraries(skiplist_test
    PRIVATE
        Catch2::Catch2
        skiplist
)

# Register tests
add_test(NAME skiplist_test_all COMMAND skiplist_test)
