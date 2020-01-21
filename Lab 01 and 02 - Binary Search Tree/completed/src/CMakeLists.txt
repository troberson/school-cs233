# Compile the main BST library
add_library (bst
    ComputerScientist.cpp
)

# Include the header files
target_include_directories(bst PUBLIC ${BST_SOURCE_DIR}/include)

# Use C++17
target_compile_features(bst PRIVATE cxx_std_17)

