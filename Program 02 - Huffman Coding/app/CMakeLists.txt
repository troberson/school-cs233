add_executable(huffman_app
    HuffmanCoding.cpp
)

file(GLOB INPUT_TEXTS "*.txt")
file(COPY ${INPUT_TEXTS} DESTINATION ".")

# Use C++17
target_compile_features(huffman_app PRIVATE cxx_std_17)

# Link to the main library
target_link_libraries(huffman_app PRIVATE huffman)
