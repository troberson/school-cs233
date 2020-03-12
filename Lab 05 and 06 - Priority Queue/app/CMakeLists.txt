add_executable(priority_app
    Driver.cpp
)

configure_file(ProcessList.txt ProcessList.txt COPYONLY)

# Use C++17
target_compile_features(priority_app PRIVATE cxx_std_17)

# Link to the main library
target_link_libraries(priority_app PRIVATE priority)
