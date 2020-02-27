# Compile the main BST library
add_library (skiplist
    ComputerScientist.cpp
)

# Include the header files
target_include_directories(skiplist PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Use C++17
target_compile_features(skiplist PRIVATE cxx_std_17)

