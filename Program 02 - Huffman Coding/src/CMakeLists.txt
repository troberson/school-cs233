# Compile the main BST library
add_library (huffman
    HuffmanTree.cpp
)

# Include the header files
target_include_directories(huffman PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Use C++17
target_compile_features(huffman PRIVATE cxx_std_17)

