# Compile the main BST library
add_library (priority
    Process.cpp
)

# Include the header files
target_include_directories(priority PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Use C++17
target_compile_features(priority PRIVATE cxx_std_17)

