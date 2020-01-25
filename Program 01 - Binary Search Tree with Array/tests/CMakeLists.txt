# Testing library
FetchContent_Declare(
catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG        v2.9.1
)
FetchContent_MakeAvailable(catch2)

add_executable(bst_test
    test_main.cpp
    BSTree_test.cpp
)

# Use C++17
target_compile_features(bst_test PRIVATE cxx_std_17)

# Link to main library, Catch2, and TRString
target_link_libraries(bst_test
    PRIVATE
        Catch2::Catch2
        bst
)

# Register tests
add_test(NAME bst_test_all COMMAND bst_test)
